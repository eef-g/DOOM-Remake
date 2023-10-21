use bevy::{
    prelude::*, 
    input::common_conditions::input_toggle_active,
    diagnostic::FrameTimeDiagnosticsPlugin
};
use bevy_inspector_egui::quick::WorldInspectorPlugin;
use bevy_rapier2d::prelude::*;

pub struct DebugPlugin;

impl Plugin for DebugPlugin {
    fn build(&self, app: &mut App) {
        app
            .add_systems(Update,
                bevy::window::close_on_esc,
            )
            .add_plugins((
                FrameTimeDiagnosticsPlugin,
                WorldInspectorPlugin::default().run_if(input_toggle_active(false, KeyCode::Tab)),
                RapierDebugRenderPlugin::default()
            ));
    }
}


// Systems
//
//
