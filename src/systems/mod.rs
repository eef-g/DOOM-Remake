// All systems files go here in the mod section
mod player_systems;
mod startup_systems;
mod pig_systems;
mod level_systems;

// Make all of the functions from the systems available to the mod
pub use player_systems::*;
pub use startup_systems::*;
pub use pig_systems::*;
pub use level_systems::*;
