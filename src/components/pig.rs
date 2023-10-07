use bevy::prelude::*;

#[derive(Component)]
pub struct Pig {
    pub lifetime: Timer,
    pub movetime: Timer,
    pub movedir: i32,
}

