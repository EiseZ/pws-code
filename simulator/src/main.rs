mod consts;
mod vector;
use crate::consts::*;
use crate::vector::Vector;

struct Simulation {
    particles: [Particle; AMOUNT_OF_CELLS],
}

impl Simulation {
    fn new() -> Simulation {
        let mut particles = [Particle::new(Vector::new(0., 0., 0.), Vector::new(0., 0., 0.), Vector::new(0., 0., 0.)); AMOUNT_OF_CELLS];
        let mut position = Vector::new(0., 0., 0.);
        for particle in particles.iter_mut() {
            particle.pos = position;
            position.x += 0.1;
        }
        Simulation {
            particles,
        }
    }

    fn calculate_force_vector(&mut self) {
        let particles_copy = self.particles.clone();
        for particle in self.particles.iter_mut() {
            let mut force = Vector::new(0., 0., 0.);
            force += GRAVITY_ACC_VECTOR * PARTICLE_MASS; // Gravity
            //force += particle.vel * (DAMPING_CONSTANT * -1.); // Damping force
            for other_particle in particles_copy { // Attraction & repulsion between particles
                if particle.pos != other_particle.pos {
                     let distance = particle.distance(&other_particle);                    
                     if distance.is_nan() {
                         continue;
                    }
                    let repulsion_force = REPULSION_FACTOR / distance.powi(2);
                    let vector_a_b = other_particle.pos - particle.pos;
                    let repulsion_force_vector = (vector_a_b / vector_a_b.len()) * repulsion_force;
                    force += repulsion_force_vector;
                }
            }
            particle.force = force;
        }
    }

    fn calculate_accelerations(&mut self) {
        for particle in self.particles.iter_mut() {
            particle.acc = particle.force / PARTICLE_MASS;
        }
    }

    fn calculate_velocities(&mut self, timestep: f32) {
        for particle in self.particles.iter_mut() {
            particle.vel += particle.acc * timestep;
        }
    }

    fn calculate_positions(&mut self, timestep: f32) {
        for particle in self.particles.iter_mut() {
            particle.pos += particle.vel * timestep;
            if particle.pos.x > 10. {
                particle.vel.x = particle.vel.x * -1.;
                particle.force.x = particle.force.x * -1.;
            } else if particle.pos.x < -10. {
                particle.vel.x = particle.vel.x * -1.;
                particle.force.x = particle.force.x * -1.;
            }
            if particle.pos.z > 10. {
                particle.vel.z = particle.vel.z * -1.;
                particle.force.z = particle.force.z * -1.;
            } else if particle.pos.z < -10. {
                particle.vel.z = particle.vel.z * -1.;
                particle.force.z = particle.force.z * -1.;
            }
            if particle.pos.y > 10. {
                particle.vel.y = particle.vel.y * -1.;
                particle.force.y = particle.force.y * -1.;
            } else if particle.pos.y < -10. {
                particle.vel.y = particle.vel.y * -1.;
                particle.force.y = particle.force.y * -1.;
            }
        }
    }

    fn current_state_to_csv(&mut self) -> String {
        let mut output = String::new();

        for particle in self.particles {
            output.push_str(&format!("{},{},{},", particle.pos.x, particle.pos.y, particle.pos.z));
        }

        // Remove trailing comma
        output.pop();

        output
    }
}

#[derive(Copy, Clone, Debug)]
struct Particle {
    pos: Vector<f32>,
    vel: Vector<f32>,
    acc: Vector<f32>,
    force: Vector<f32>,
}

impl Particle {
    fn new(pos: Vector<f32>, vel: Vector<f32>, acc: Vector<f32>) -> Particle {
        Particle {
            pos,
            vel,
            acc,
            force: Vector::new(0., 0., 0.),
        }
    }

    fn distance(&self, particle: &Particle) -> f32 {
        let pos1 = self.pos;
        let pos2 = particle.pos;
        let distance = ((pos2.x - pos1.x).powi(2) + (pos2.y - pos1.y).powi(2) + (pos2.z - pos1.z).powi(2)).sqrt();
        distance
    }
}

use std::env;
use std::fs::File;
use std::io::prelude::*;
fn main() {
    // Parse args
    let args: Vec<String> = env::args().collect();
    let filename = {
        if args.len() > 1 {
            args[1].clone()
        } else {
            String::from("output.csv")
        }
    };
    { // Empty the file
        File::create(&filename).expect("[Error] Failed to open file");
    }

    // Main loop
    let mut current_time: f32 = 0.;
    let mut simulation = Simulation::new();
    while current_time < MAX_TIME {
        simulation.calculate_force_vector();
        simulation.calculate_accelerations();
        simulation.calculate_velocities(TIMESTEP);
        simulation.calculate_positions(TIMESTEP);

        let mut file = File::options().write(true).append(true).open(&filename).expect("[Error] Failed toi open file");
        writeln!(file, "{}", simulation.current_state_to_csv()).expect(&format!("Failed to write to file at time: {}", current_time));

        current_time += TIMESTEP;
    }

}
