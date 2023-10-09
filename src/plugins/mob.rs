use bevy::{prelude::*, sprite::collide_aabb::collide};
use crate::plugins::*;

pub struct MobPlugin;

impl Plugin for MobPlugin {
    fn build(&self, app: &mut App) {
        app
            .add_plugins((
                PlayerPlugin,
                PigPlugin
            ))
            .add_systems(Update, collision_check);
    }
}


#[derive(Component)]
pub struct Mob{
    pub is_colliding: bool,
    pub target_delta_x: Vec3,
    pub target_delta_y: Vec3
}

pub fn collision_check(
    wall_query: Query<&Transform, (With<TileCollider>, Without<Mob>)>,
    mob_query: Query<&Mob>
){ 
    for mob in  mob_query {
        let mut mob_collision = false;
        for wall_transform in wall_query.iter() { 
            // Check if there is a collision with the delta_x target
            let collision = collide(
                mob.target_delta_x, 
                Vec2::splat(16.0 * 0.9),
                wall_transform.translation,
                Vec2::splat(16.0) // This has to be <= the tile_size that we are using
            );
            if collision.is_some() {
                mob_collision = true;
                break;
            }
            // Now check on the delta_y target
            let collision = collide(
                mob.target_delta_y,
                Vec2::splat(16.0 * 0.9),
                wall_transform.translation,
                Vec2::splat(16.0)
            );
            if collision.is_some() {
                mob_collision = true;
                break;
            }
        }
        mob.is_colliding = mob_collision;
    }
}
