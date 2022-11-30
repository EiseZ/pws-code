use crate::vector::Vector;

// Simulation properties
pub const AMOUNT_OF_CELLS: usize = 100;
pub const MAX_TIME: f32 = 10.;
pub const TIMESTEP: f32 = 0.01;
pub const SIMULATION_SIZE: f32 = 1.;

// Constants for formula's
pub const GRAVITY_ACC_VECTOR: Vector<f32> = Vector { x: 0., y: -9.81, z: 0. };
pub const DAMPING_CONSTANT: f32 = 1.; // TODO: What is good value for this?
pub const REPULSION_FACTOR: f32 = 0.0001;
                                                      //
// Particle properties
pub const PARTICLE_MASS: f32 = 1.; // TODO: Calculate based on dimentions
pub const PARTICLE_RADIUS: f32 = 0.05;
