// All systems files go here in the mod section
mod player_systems;
mod startup_systems;
mod pig_systems;

// This is the public interface for the game_systems module
pub use player_systems::*;

// Startup systems
pub use startup_systems::*;

// Spawn systems
pub use pig_systems::*;
