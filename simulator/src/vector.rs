#[derive(Copy, Clone, PartialEq, Debug)]
pub struct Vector<T> {
    pub x: T,
    pub y: T,
    pub z: T,
}

impl<T> Vector<T> {
    pub fn new(x: T, y: T, z: T) -> Vector<T> {
        Vector {
            x,
            y,
            z,
        }
    }
}

impl Vector<f32> {
    pub fn len(&self) -> f32 {
        return (self.x.powi(2) + self.y.powi(2) + self.z.powi(2)).sqrt();
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

impl std::ops::Div<f32> for Vector<f32> {
    type Output = Vector<f32>;
    fn div(self, rhs: f32) -> Vector<f32> {
        Vector {
            x: self.x / rhs,
            y: self.y / rhs,
            z: self.z / rhs,
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

impl std::ops::AddAssign<f32> for Vector<f32> {
    fn add_assign(&mut self, rhs: f32) {
        *self = Self {
            x: self.x + rhs,
            y: self.y + rhs,
            z: self.z + rhs,
        }
    }
}

impl std::ops::Sub for Vector<f32> {
    type Output = Vector<f32>;
    fn sub(self, rhs: Self) -> Vector<f32> {
        Vector {
            x: self.y - rhs.x,
            y: self.y - rhs.y,
            z: self.z - rhs.z,
        }
    }
}
