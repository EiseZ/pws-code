// Settings
const AMOUNT_OF_CELLS: usize = 100;

struct Simulation {
    particles: [Particle; AMOUNT_OF_CELLS],
}

const GRAVITY_ACC_VECTOR: Vector<f32> = Vector { x: 0., y: -9.81, z: 0. };
const DAMPING_CONSTANT: f32 = 1.; // TODO: What is good value for this?
const ATTRACTION_EXPONENT: i32 = 6;
const REPULSION_EXPONENT: i32 = 12;
const ATTRACTION_FACTOR: f32 = 0.000000000000000002737205; // TODO: What is good value for this?
const REPULSION_FACTOR: f32 = 377616490000000000000.; // TODO: What is good value for this?
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
                    let attraction_force = REPULSION_FACTOR as f32 / (distance.powi(REPULSION_EXPONENT)) - ATTRACTION_EXPONENT as f32 / (distance.powi(ATTRACTION_EXPONENT));
                    // TODO: Calculate angle of attraction/rupulsion force and convect to vector,
                    // than add to force
                }
            }
            particle.force = force;
        }
    }
}

const PARTICLE_MASS: f32 = 0.01; // TODO: Calculate based on dimentions
#[derive(Copy, Clone)]
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

#[derive(Copy, Clone, PartialEq)]
struct Vector<T> {
    x: T,
    y: T,
    z: T,
}

impl<T> Vector<T> {
    fn new(x: T, y: T, z: T) -> Vector<T> {
        Vector {
            x,
            y,
            z,
        }
    }
}

impl std::ops::Mul<f32> for Vector<f32> {
    type Output = Vector<f32>;
    fn mul(self, rhs: f32) -> Vector<f32> {
        Vector {
            x: self.x * rhs,
            y: self.y * rhs,
            z: self.z * rhs,
        }
    }
}

impl std::ops::AddAssign for Vector<f32> {
    fn add_assign(&mut self, rhs: Self) {
        *self = Self {
            x: self.x + rhs.x,
            y: self.y + rhs.y,
            z: self.z + rhs.z,
        }
    }
}

const MAX_TIME: f32 = 10.;
const TIMESTEP: f32 = .01;

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
        let mut file = File::create(filename).expect("[Error] Failed to open file");
    }

    // Main loop
    let mut current_time: f32 = 0.;
    while current_time < MAX_TIME {

        let mut file = File::options().write(true).append(true).open(filename).expect("[Error] Failed toi open file");
        writeln!(file, "new timestep");

        current_time += TIMESTEP;
    }

    let mut simulation = Simulation::new();
    simulation.calculate_force_vector();
    //simulation.calculate_accelerations();
    //simulation.calculate_velocities();
    //simulation.calculate_positions();
}
