use bevy::prelude::*;
use bevy::input::common_conditions::input_toggle_active;
use bevy_inspector_egui::quick::WorldInspectorPlugin;

pub struct DebugPlugin;

impl Plugin for DebugPlugin {
    fn build(&self, app: &mut App) {
        app
            .add_systems(Update,
                bevy::window::close_on_esc,
            )
            .add_plugins(WorldInspectorPlugin::default().run_if(input_toggle_active(false, KeyCode::Tab)));

    }
}
