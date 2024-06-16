#pragma once

#include "fast_array.hpp"
#include "vec2.hpp"
#include "physic_body.hpp"
#include "access_grid.hpp"
#include <SFML/System/Clock.hpp>
#include <iostream>
#include "segment.hpp"
#include "swarm.hpp"

constexpr uint32_t GRID_CELL_SIZE = 24U;

namespace up
{
	class CollisionSolver
	{
	public:
		CollisionSolver() = default;
		CollisionSolver(const Vec2& dimension, float body_radius, std::vector<Body>& bodies, const Vec2& gravity = Vec2(0.0f, 0.0f))
			: m_dimension(dimension)
			, m_gravity(gravity)
			, m_precision(1)
			, m_body_radius(body_radius)
			, m_grid(dimension, 4 * uint32_t(body_radius), bodies)
			, m_swarm(16)
		{
		}

		void update(fva::SwapArray<Body>& bodies, fva::SwapArray<SolidSegment>& segments, float dt)
		{
			applyGravity(bodies);

			collision_time = 0.0f;
			grid_time = 0.0f;

			sf::Clock clock_global, clock_local;

			clock_local.restart();
			solveBoundaryCollisions(bodies);
			m_grid.addBodies(bodies.getData());
			m_grid.addSegments(segments.getData());
			
			grid_time += clock_local.getElapsedTime().asMicroseconds() * 0.001f;

			for (m_current_iteration = 0; m_current_iteration <m_precision; ++m_current_iteration) {
				clock_local.restart();
				swrm::WorkGroup group = m_swarm.execute([this](uint32_t id, uint32_t worker_count) {solveCollisionsSwarm(id, worker_count, m_grid.getCells()); });
				group.waitExecutionDone();				
				collision_time += clock_local.getElapsedTime().asMicroseconds() * 0.001f;
				solveBoundaryCollisions(bodies);
			}

			total_update_time = clock_global.getElapsedTime().asMicroseconds() * 0.001f;
		}

		const Vec2& dimension() const
		{
			return m_dimension;
		}

		float defaultBodyRadius() const
		{
			return m_body_radius;
		}

		up::Body* getBodyAt(const up::Vec2& position, fva::SwapArray<Body>& bodies)
		{
			for (up::Body& b : bodies) 
			{
				float dist = (position - b.position()).length();

				if (dist < b.radius) {
					return &b;
				}
			}

			return nullptr;
		}

		const Grid<GRID_CELL_SIZE>& getGrid() const
		{
			return m_grid;
		}

		bool test_pressure = false;
		float total_update_time;
		float collision_time;
		float grid_time;

	private:
		Vec2 m_gravity;
		Grid<GRID_CELL_SIZE> m_grid;
		swrm::Swarm m_swarm;

		const Vec2 m_dimension;
		const uint32_t m_precision;
		const float m_body_radius;
		uint32_t m_current_iteration;

		void applyGravity(fva::SwapArray<Body>& bodies)
		{
			for (Body& b : bodies) {
				b.accelerate(m_gravity);
			}
		}

		void solveBoundaryCollisions(fva::SwapArray<Body>& bodies)
		{
			for (Body& b : bodies) {
				Vec2 pos = b.position();
				float radius = b.radius;
				if (pos.x < radius) {
					b.move({ radius - pos.x, 0.0f });
					//b.stop();
				} else if (pos.x > m_dimension.x - radius) {
					b.move({ m_dimension.x - radius - pos.x, 0.0f });
					//b.stop();
				}

				if (pos.y < radius) {
					b.move({ 0.0f, radius - pos.y });
					//b.stop();
				} else if (pos.y > m_dimension.y - radius) {
					b.move({ 0.0f, m_dimension.y - radius - pos.y });
					//b.stop();
				}
			}
		}

		void solveCollisionsSwarm(uint32_t id, uint32_t worker_count, std::vector<GridCell<GRID_CELL_SIZE>>& data)
		{
			const uint32_t size = static_cast<uint32_t>(data.size());

			uint32_t step_size(size / worker_count);
			uint32_t start_index(id * step_size);
			uint32_t end_index(start_index + step_size);

			if (m_current_iteration % 2) {
				for (uint32_t cell_id(step_size - 1); cell_id--;) {
					GridCell<GRID_CELL_SIZE>& cell = data[start_index + cell_id];
					const uint32_t size(cell.item_count);
					solveCellCollisions(size, cell.items);
				}
			}
			else {
				for (uint32_t cell_id(0); cell_id<step_size; ++cell_id) {
					GridCell<GRID_CELL_SIZE>& cell = data[start_index + cell_id];
					const uint32_t size(cell.item_count);
					solveCellCollisions(size, cell.items);
				}
			}
		}

		void solveCellCollisions(uint32_t size, std::array<up::Body*, GRID_CELL_SIZE>& bodies)
		{
			for (uint32_t i(0); i < size; ++i) {
				Body& b1(*bodies[i]);
				for (uint32_t k(i + 1); k < size; ++k) {
					Body& b2(*bodies[k]);
					solveBodiesCollision(b1, b2);
				}
			}
		}

		void solveBodiesCollision(Body& b1, Body& b2)
		{
			const float col_radius(2*m_body_radius);
			Vec2 col_axe(b1.position() - b2.position());
			const float length2(col_axe.length2());
			if (length2 < col_radius*col_radius && length2 > 0.01f)
			{
				const float m1(b1.inertia);
				const float m2(b2.inertia);
				const float mass_tot(1.0f / (m1 + m2));
				const float mass_factor_1(m1 * mass_tot);
				const float mass_factor_2(m2 * mass_tot);
				const float delta_col(0.5f * (col_radius - col_axe.length()));

				col_axe.normalize();
				b1.move(col_axe*( delta_col * mass_factor_2));
				b2.move(col_axe*(-delta_col * mass_factor_1));

				const float cohesion(0.1f);
				const Vec2 delta_v(b1.velocity() - b2.velocity());
				b1.setVelocity(-(cohesion)*delta_v);
				b2.setVelocity( (cohesion)*delta_v);
				b1.addPressure(delta_col);
				b2.addPressure(delta_col);
			}
		}

		void solveSegmentsCollisions(std::vector<GridCell<GRID_CELL_SIZE>>& data)
		{
			for (GridCell<GRID_CELL_SIZE>& cell : data) {
				solveBodySegment(cell.segments, cell.items, cell.item_count);
				//solveSegmentSegment(cell.segments);
			}
		}

		void solveBodySegment(std::vector<SolidSegment*>& segments, std::array<up::Body*, GRID_CELL_SIZE>& bodies, uint32_t size)
		{
			for (SolidSegment* s : segments) {
				for (uint32_t i(0); i < size; ++i) {
					s->collideWith(*bodies[i]);
				}
			}
		}

		void solveSegmentSegment(std::vector<SolidSegment*>& segments)
		{
			for (SolidSegment* s1 : segments) {
				for (SolidSegment* s2 : segments) {
					if (s1 != s2) {
						s1->collideWith(*s2);
					}
				}
			}
		}

		void naive_segments_segments(std::vector<SolidSegment>& segments)
		{
			for (SolidSegment& s1 : segments) {
				for (SolidSegment& s2 : segments) {
					if (&s1 != &s2) {
						s1.collideWith(s2);
					}
				}
			}
		}

		void naive_segments_bodies(std::vector<SolidSegment>& segments, std::vector<up::Body>& bodies)
		{
			for (SolidSegment& s1 : segments) {
				for (Body& b : bodies) {
					s1.collideWith(b);
				}
			}
		}
	};
}



