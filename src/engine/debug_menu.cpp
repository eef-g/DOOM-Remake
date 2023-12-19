#include "debug_menu.hpp"

DebugMenu::DebugMenu() {
}

void DebugMenu::Show() {
    bool open = true;
    ImGui::Begin("JDAC Debug Tool", &open, ImGuiWindowFlags_NoScrollbar);

    // Show the current wad file
    std::string wadName = "Current WAD File: doom1.wad";
    ImGui::Text(wadName.c_str());
    if(ImGui::CollapsingHeader("WAD Info"))
    {
        ImGui::Text("Number of Lumps: {}");
    }
    ImGui::Spacing();

    if(ImGui::CollapsingHeader("Maps"))
    {

        ImGui::BeginChild("Scrolling");
        for(int i = 0; i < 9; i++) {
            std::string text = "Option " + i;
            ImGui::Text(text.c_str());
        }
        ImGui::EndChild();
        
    }

   
    if (ImGui::CollapsingHeader("Map Lumps")) {
        ImGui::Text("Current Map E1M1");
        ImGui::BeginChild("Scrolling");
        for(int i = 0; i < 12; i++) {
            std::string lumpName = "Lump " + i;
            ImGui::Button(lumpName.c_str());
        }
        ImGui::EndChild();
    }
    ImGui::Spacing();
    
    if (ImGui::CollapsingHeader("Lump Data")) {
        ImGui::Text("Current Lump: {}");
        // Insert a table of the lump data here
    }
    ImGui::Spacing();
    
    ImGui::End();
}
