#include <CTRPluginFramework.hpp>
#include "cheats.hpp"
#include "RegionCodes.hpp"
#include "TextFileParser.hpp"

namespace CTRPluginFramework {
//Infinite Fruit Tree
	void fruitStays(MenuEntry *entry) {
		static const u32 fruitstay1 = Region::AutoRegion(0x5972D4, 0x5967EC, 0x59631C, 0x59631C, 0x595C0C, 0x595C0C, 0x5958E0, 0x5958E0);
		static const u32 fruitstay2 = Region::AutoRegion(0x5972CC, 0x5967E4, 0x596314, 0x596314, 0x595C04, 0x595C04, 0x5958D8, 0x5958D8);
		
		std::vector<std::string> cmnOpt =  { "" };

		bool IsON = *(u32 *)fruitstay1 == 0xE58D101C;

		cmnOpt[0] = (IsON ? Color(pGreen) << Language->Get("VECTOR_ENABLED") : Color(pRed) << Language->Get("VECTOR_DISABLED"));
		
		Keyboard optKb(Language->Get("KEY_CHOOSE_OPTION"));
		optKb.Populate(cmnOpt);
		Sleep(Milliseconds(100));
		int op = optKb.Open();
		if(op == -1)
			return;
			
		Process::Patch(fruitstay1, *(u32 *)fruitstay1 == 0xE58D101C ? 0xEB00054D : 0xE58D101C);
		Process::Patch(fruitstay2, *(u32 *)fruitstay2 == 0xE5961000 ? 0xE1A01006 : 0xE5961000);
		fruitStays(entry);
	}
//Axe Tree Shake	
	void shakechop(MenuEntry *entry) {
		static const u32 shake1 = Region::AutoRegion(0x5971D4, 0x5966EC, 0x59621C, 0x59621C, 0x595B0C, 0x595B0C, 0x5957E0, 0x5957E0);
		static const u32 shake2 = Region::AutoRegion(0x5971DC, 0x5966F4, 0x596224, 0x596224, 0x595B14, 0x595B14, 0x5957E8, 0x5957E8);
		static const u32 shake3 = Region::AutoRegion(0x5971E4, 0x5966FC, 0x59622C, 0x59622C, 0x595B1C, 0x595B1C, 0x5957F0, 0x5957F0);
		static const u32 shake4 = Region::AutoRegion(0x5971EC, 0x596704, 0x596234, 0x596234, 0x595B24, 0x595B24, 0x5957F8, 0x5957F8);
		
		std::vector<std::string> cmnOpt =  { "" };
		
		bool IsON = *(u32 *)shake1 == 0xE1A00000;

		cmnOpt[0] = (IsON ? Color(pGreen) << Language->Get("VECTOR_ENABLED") : Color(pRed) << Language->Get("VECTOR_DISABLED"));
		
		Keyboard optKb(Language->Get("KEY_CHOOSE_OPTION"));
        optKb.Populate(cmnOpt);
		Sleep(Milliseconds(100));
		s8 op = optKb.Open();
		if(op < 0)
			return;
			
		Process::Patch(shake1, *(u32 *)shake1 == 0xE1A00000 ? 0x0A000008 : 0xE1A00000);
		Process::Patch(shake2, *(u32 *)shake2 == 0xE1A00000 ? 0x0A00005B : 0xE1A00000);
		Process::Patch(shake3, *(u32 *)shake3 == 0x1A00001B ? 0x0A00001B : 0x1A00001B);
		Process::Patch(shake4, *(u32 *)shake4 == 0xEA000080 ? 0x0A000080 : 0xEA000080);	
		shakechop(entry);
    }
//Fruit Tree Item Modifier	
	void fruititemmod(MenuEntry *entry) {
		static const u32 fruitmod = Region::AutoRegion(0x2FE6A0, 0x2FE510, 0x2FE5E8, 0x2FE5E8, 0x2FE5AC, 0x2FE5AC, 0x2FE5D0, 0x2FE5D0);
		
		static u32 val = 0x2018;
		if(entry->WasJustActivated()) {
			Process::Patch(fruitmod, 0xE59F0020); 
            Process::Write32(fruitmod + 0xC, 0xE3500000); 
			Process::Patch(fruitmod + 0x28, val);
		}
		
		if(entry->Hotkeys[0].IsDown()) {
			if(Wrap::KB<u32>(Language->Get("ENTER_ID"), true, 8, val, val)) 
				Process::Patch(fruitmod + 0x28, val);
		}
		
		if(!entry->IsActivated()) {
			Process::Patch(fruitmod, 0xE59F1020);
			Process::Patch(fruitmod + 0xC, 0xE1510002);
			Process::Patch(fruitmod + 0x28, 0x172B);
		}
	}
//Instant Tree Chop	
	void instantchop(MenuEntry *entry) { 
		static const u32 instchop = Region::AutoRegion(0x59945C, 0x598974, 0x5984A4, 0x5984A4, 0x597D94, 0x597D94, 0x597A68, 0x597A68);
		if(entry->WasJustActivated()) 
			Process::Patch(instchop, 0xE1A00000); 
		else if(!entry->IsActivated()) 
			Process::Patch(instchop, 0xCA000005); 
	}
}