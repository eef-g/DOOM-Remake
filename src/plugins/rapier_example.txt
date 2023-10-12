use bevy::prelude::*;
use bevy_rapier2d::prelude::*;

pub struct RapierExamplePlugin;

impl Plugin for RapierExamplePlugin {
     fn build(&self, app: &mut App) {
        app
         .add_plugins((
                RapierPhysicsPlugin::<NoUserData>::pixels_per_meter(100.0),
        ))
        .add_systems(Startup, (
            setup_graphics,
            spawn_player
        ))
        .add_systems(Update, (
            update_controllers
        ));
    }
}

fn setup_physics(mut commands: Commands) {
    // Rapier example code
    // /* Create the ground. */
    // commands
    //     .spawn(Collider::cuboid(500.0, 50.0))
    //     .insert(TransformBundle::from(Transform::from_xyz(0.0, -100.0,
    //     0.0)
    // ));
    // /* Create the bouncing ball. */
    // commands
    //     .spawn(RigidBody::Dynamic)
    //     .insert(Collider::ball(50.0))
    //     .insert(Restitution::coefficient(0.7))
    //     .insert(TransformBundle::from(Transform::from_xyz(0.0, 400.0,
    //     0.0)
    // ));

    spawn_ground(&mut commands);
    spawn_shape(&mut commands);
}

fn setup_graphics(mut commands: Commands) {
    // Add a camera so we can see the debug-render.
    commands.spawn(Camera2dBundle::default());
}

// This function is one of my own creation
fn spawn_shape(commands: &mut Commands) {
    commands
        .spawn(RigidBody::Dynamic)
        .insert(Collider::capsule(Vec2::new(0.0, 0.0), Vec2::new(0.0, 50.0), 25.0))
        .insert(TransformBundle::from(Transform::from_xyz(0.0, 400.0, 0.0)
    ));
}

fn spawn_ground(commands: &mut Commands) {
    // Make the floor
    commands
        .spawn(Collider::cuboid(1000.0, 50.0))
        .insert(TransformBundle::from(Transform::from_xyz(0.0, -100.0, 0.0)));
}

fn spawn_player(mut commands: Commands) {
    spawn_ground(&mut commands);
    commands
        .spawn(RigidBody::KinematicPositionBased)
        .insert(TransformBundle::from(Transform::from_xyz(0., 0., 0.)))
        .insert(Collider::capsule(Vec2::splat(0.0), Vec2::new(0.0, 50.0), 25.0))
        .insert(KinematicCharacterController::default());
}

// Move the controller downwards automatically (Like gravity) 
fn update_controllers(
    mut controllers: Query<&mut KinematicCharacterController>,
    input: Res<Input<KeyCode>>,
    time: Res<Time>
) {
    for mut controller in controllers.iter_mut() {
        let move_amount = 500.0 * time.delta_seconds();
        let mut delta_x = 0.0;
        let mut delta_y = 0.0;

        if input.pressed(KeyCode::W) {
            delta_y += move_amount;
        }
        if input.pressed(KeyCode::S) {
            delta_y -= move_amount;
        }
        if input.pressed(KeyCode::D) {
            delta_x += move_amount;
            // sprite.flip_x = false;
            
        }
        if input.pressed(KeyCode::A) {
            delta_x -= move_amount;
            // sprite.flip_x = true;
        }
        controller.translation = Some(Vec2::new(delta_x, delta_y));
    }
}
