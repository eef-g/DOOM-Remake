use bevy::prelude::*;
// #[path="../game_components/mod.rs"] mod game_components;
use crate::components as c;


pub fn character_movement(
    mut characters: Query<(&mut Transform, &c::Player, &mut Sprite)>,
    input: Res<Input<KeyCode>>,
    time: Res<Time>,
) {
    for (mut transform, player, mut sprite) in &mut characters {
        let move_amount = player.speed * time.delta_seconds();
        if input.pressed(KeyCode::W) {
            transform.translation.y += move_amount;
        }
        if input.pressed(KeyCode::S) {
            transform.translation.y -= move_amount;
        }
        if input.pressed(KeyCode::D) {
            transform.translation.x += move_amount;
            sprite.flip_x = false;
            
        }
        if input.pressed(KeyCode::A) {
            transform.translation.x -= move_amount;
            sprite.flip_x = true;
        }
    }
}

