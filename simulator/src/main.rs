mod consts;
mod vector;
use crate::consts::*;
use crate::vector::Vector;

struct Simulation {
    particles: [Particle; AMOUNT_OF_CELLS],
}

impl Simulation {
    fn new() -> Simulation {
        Simulation {
            particles: [Particle::new(Vector::new(0., 0., 0.), Vector::new(0., 0., 0.), Vector::new(0., 0., 0.)); AMOUNT_OF_CELLS],
        }
    }

    fn calculate_force_vector(&mut self) {
        for mut particle in self.particles {
            let mut force = particle.force;
            force += GRAVITY_ACC_VECTOR * PARTICLE_MASS; // Gravity
            force += particle.vel * (DAMPING_CONSTANT * -1.); // Damping force
            for other_particle in self.particles { // Attraction & repulsion between particles
                if particle.pos != other_particle.pos {
                    let distance = particle.distance(&other_particle);
                    let repulsion_force = REPULSION_FACTOR / distance.pow(2);
                }
            }
            particle.force = force;
        }
    }

    fn current_state_to_csv(&mut self) -> String {
        let mut output = String::new();

        for particle in self.particles {
            output.push_str(&format!("{},{},{},", particle.pos.x, particle.pos.y, particle.pos.z));
        }

        output
    }
}

#[derive(Copy)]
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
        let distance = (pos2.x - pos1.x).powi(2) + (pos2.y - pos1.y).powi(2) + (pos2.z - pos1.z).powi(2);
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
        //simulation.calculate_accelerations();
        //simulation.calculate_velocities();
        //simulation.calculate_positions();

        let mut file = File::options().write(true).append(true).open(&filename).expect("[Error] Failed toi open file");
        writeln!(file, "{}", simulation.current_state_to_csv()).expect(&format!("Failed to write to file at time: {}", current_time));

        current_time += TIMESTEP;
    }

}
