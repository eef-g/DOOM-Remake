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
            .register_type::<Mob>();
    }
}


#[derive(Component, Default, Reflect)]
#[reflect(Component)]
pub struct Mob{
    pub target_delta_x: Vec3,
    pub target_delta_y: Vec3
}

fn collision_check(
    wall_query: &Query<&Transform, (With<TileCollider>, Without<Mob>)>,
    target: Vec3
) -> bool{ 
    for wall_transform in wall_query.iter() { 
        // Check if there is a collision with the delta_x target
        let collision = collide(
            target,
            Vec2::splat(16.0 * 0.9),
            wall_transform.translation,
            Vec2::splat(16.0) // This has to be <= the tile_size that we are using
        );
        if collision.is_some() 
        {
            return true;
        }
    }
    return false;
}

pub fn move_mob(
    wall_query: &Query<&Transform, (With<TileCollider>, Without<Mob>)>,
    transform: &mut Transform,
    mob: &mut Mob,
    delta_x: f32,
    delta_y: f32
) {
    if delta_x != 0.0 || delta_y != 0.0 { 
        mob.target_delta_x = transform.translation + Vec3::new(delta_x, 0.0, 0.0); 
        if !collision_check(&wall_query, mob.target_delta_x) {
            transform.translation += Vec3::new(delta_x, 0.0, 0.0);
        }

        mob.target_delta_y = transform.translation + Vec3::new(0.0, delta_y, 0.0);
        if !collision_check(&wall_query, mob.target_delta_y){
            transform.translation += Vec3::new(0.0, delta_y, 0.0);
        }
    }
}
