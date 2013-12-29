#include "g_local.h"

// Output is stored in digestWithNullTerm (char[16] = digest(15) + \0)
void hashPassword(const char *pw, char *digestWithNullTerm)
{
    const char* saltMD5 = "(_55)pE*mLQ#)";    // length = 13 without null
    char combinedStr[32 + 13 + 1];
    md5_state_t stateMD5;
    md5_byte_t digestMD5[16];

    memcpy(combinedStr, pw, 32);
    memcpy(combinedStr + 32, saltMD5, 13);
    combinedStr[45] = '\0';

    md5_init(&stateMD5);
    md5_append(&stateMD5, (const md5_byte_t *)combinedStr, 45);
    md5_finish(&stateMD5, (md5_byte_t *)digestMD5);

    memcpy(digestWithNullTerm, digestMD5, 16);
    digestWithNullTerm[15] = '\0';
}

int checkString(char *input, char test)
{
	int i;
	for (i = 0; input[i] != 0; i++) {
		if (input[i] == test) {
			return 1;
		}
	}
	return 0;
}

int checkName(edict_t *ent, char *name) {
	if (strlen(name) < 3) {
		gi.cprintf(ent, PRINT_HIGH, "Your name must be atleast 3 letters\n");
		return 0;
	}
	if (checkString(name, ' ')) {
		gi.cprintf(ent, PRINT_HIGH, "Your name may not contain spaces\n");
		return 0;
	}
	if (checkString(name, '.')) {
		gi.cprintf(ent, PRINT_HIGH, "Your name may not contain '.'\n");
		return 0;
	}
	if (checkString(name, '/')) {
		gi.cprintf(ent, PRINT_HIGH, "Your name may not contain '/'\n");
		return 0;
	}
	if (checkString(name, '\\')) {
		gi.cprintf(ent, PRINT_HIGH, "Your name may not contain '\'\n");
		return 0;
	}
	if (checkString(name, '*')) {
		gi.cprintf(ent, PRINT_HIGH, "Your name may not contain '*'\n");
		return 0;
	}
	if (checkString(name, '?')) {
		gi.cprintf(ent, PRINT_HIGH, "Your name may not contain '?'\n");
		return 0;
	}
	if (checkString(name, '$')) {
		gi.cprintf(ent, PRINT_HIGH, "Your name may not contain '$'\n");
		return 0;
	}
	if (checkString(name, '<')) {
		gi.cprintf(ent, PRINT_HIGH, "Your name may not contain '<'\n");
		return 0;
	}
	if (checkString(name, '>')) {
		gi.cprintf(ent, PRINT_HIGH, "Your name may not contain '>'\n");
		return 0;
	}
	if (checkString(name, ':')) {
		gi.cprintf(ent, PRINT_HIGH, "Your name may not contain ':'\n");
		return 0;
	}
	if (checkString(name, '|')) {
		gi.cprintf(ent, PRINT_HIGH, "Your name may not contain '|'\n");
		return 0;
	}
	return 1;
}

void createNewSkills(edict_t *ent, int classId) {
	int i;
	if (!ent->client)
		return;
	memset(&ent->client->pers.skills, 0, sizeof(skills_t));

	ent->client->pers.skills.active_powerup = 0;

	ent->client->pers.skills.itemId[0] = 1; //Give Blaster
	if (classId == 0) { //Soldier
		ent->client->pers.skills.itemId[1] = 3; //SSG
		ent->client->pers.skills.itemId[2] = 5; //CG
		ent->client->pers.skills.itemId[3] = 7; //GL
		ent->client->pers.skills.itemId[4] = 8; //RL
		ent->client->pers.skills.itemId[5] = 9; //HB
		ent->client->pers.skills.itemId[6] = 10; //RG
		ent->client->pers.skills.itemId[7] = 11; //Bfg
		ent->client->pers.skills.itemId[8] = 12; //Give him LightArmor

		ent->client->pers.skills.powerup_type[0] = 1; //Weapon damage
		ent->client->pers.skills.powerup_level[0] = 10;
		ent->client->pers.skills.powerup_type[1] = 7; //Projectile speed
		ent->client->pers.skills.powerup_level[1] = 3;
	} else if (classId == 1) { //Tank
		ent->client->pers.skills.itemId[1] = 2; //SG
		ent->client->pers.skills.itemId[2] = 3; //SSG
		ent->client->pers.skills.itemId[3] = 4; //MG
		ent->client->pers.skills.itemId[4] = 8; //RL
		ent->client->pers.skills.itemId[5] = 10; //RG
		ent->client->pers.skills.itemId[6] = 12; //Light armor
		ent->client->pers.skills.itemId[7] = 34; //Give him CombatArmor

		ent->client->pers.skills.powerup_type[0] = 27; //Max armor
		ent->client->pers.skills.powerup_level[0] = 10;
		ent->client->pers.skills.powerup_type[1] = 23; //Armor eff
		ent->client->pers.skills.powerup_level[1] = 3;
		ent->client->pers.skills.powerup_type[2] = 31; //Armor regen
		ent->client->pers.skills.powerup_level[2] = 2;
	} else if (classId == 2) { //Cleric
		ent->client->pers.skills.itemId[1] = 2; //SG
		ent->client->pers.skills.itemId[2] = 4; //MG
		ent->client->pers.skills.itemId[3] = 6; //HG
		ent->client->pers.skills.itemId[4] = 19; //Shotty
		ent->client->pers.skills.itemId[5] = 12; //Give him LightArmor
		ent->client->pers.skills.itemId[6] = 27; //Give him LifeVest

		ent->client->pers.skills.powerup_type[0] = 26; //Max health
		ent->client->pers.skills.powerup_level[0] = 10;
		ent->client->pers.skills.powerup_type[1] = 56; //Create health
		ent->client->pers.skills.powerup_level[1] = 5;
		ent->client->pers.skills.powerup_type[2] = 57; //Create armor
		ent->client->pers.skills.powerup_level[2] = 5;
		ent->client->pers.skills.powerup_type[3] = 66; //Regen aura
		ent->client->pers.skills.powerup_level[3] = 5;
	} else if (classId == 3) { //Mage
		ent->client->pers.skills.itemId[1] = 2; //SG
		ent->client->pers.skills.itemId[2] = 4; //MG
		ent->client->pers.skills.itemId[3] = 9; //HB
		ent->client->pers.skills.itemId[4] = 22; //Wand
		ent->client->pers.skills.itemId[5] = 12; //Give him LightArmor

		ent->client->pers.skills.powerup_type[0] = 47; //Fireball
		ent->client->pers.skills.powerup_level[0] = 5;
		ent->client->pers.skills.powerup_type[1] = 53; //Plague bomb
		ent->client->pers.skills.powerup_level[1] = 5;
		ent->client->pers.skills.powerup_type[2] = 50; //Lightning
		ent->client->pers.skills.powerup_level[2] = 5;
	} else if (classId == 4) { //Vampire
		ent->client->pers.skills.itemId[1] = 2; //SG
		ent->client->pers.skills.itemId[2] = 3; //SSG
		ent->client->pers.skills.itemId[3] = 4; //MG
		ent->client->pers.skills.itemId[4] = 9; //HB
		ent->client->pers.skills.itemId[5] = 140; //Arm

		ent->client->pers.skills.powerup_type[0] = 1; //Weapon damage
		ent->client->pers.skills.powerup_level[0] = 10;
	}

	ent->client->pers.skills.wornItem[0] = -1;
	ent->client->pers.skills.activatingItem[0] = 0; //Make him wield the Blaster
	for (i = 1; i < GIEX_BASEITEMS; i++) {
		ent->client->pers.skills.wornItem[i] = -1;
		ent->client->pers.skills.activatingItem[i] = -1;
	}
	ent->client->pers.itemchanging = -1; // set client ready to equip items
	updateItemLevels(ent);
//	info = getItemInfo(1);
//	ent->client->newweapon = info->item;

	ApplyMax(ent);
	ent->health = ent->max_health;
	ent->client->magic = ent->client->max_magic;
}

int newCharacter(edict_t *ent, int classId, char *password)
{
	FILE *file;
	char path[128];
    char hashedPass[16];

	createNewSkills(ent, classId);
	sprintf(path, "%s/%s.ccs", charpath->string, ent->client->pers.netname);

	if ((file = fopen(path, "rb")) == NULL)
    {
		if (strlen(password) < 3)
        {
			gi.cprintf(ent, PRINT_HIGH, "You must supply a password of at least 3 letters.\n");
			ent->client->pers.loggedin = false;
			ApplyMax(ent);
			return 0;
		}
		ent->client->pers.skills.activeClass = classId;
		ent->radius_dmg = 0;
		ent->count = 0;

		ent->client->pers.expRemain = getClassExpLeft(ent, ent->client->pers.skills.activeClass);
		ent->client->pers.itemchanging = -1; // set client ready to equip items

        // User can enter a password up to 31 chars
        // Password is salted, MD5 hashed, and then stored in the character file
        hashPassword(password, hashedPass);
		memcpy(ent->client->pers.skills.password, hashedPass, 16);
        gi.cprintf(ent, PRINT_HIGH, "Creating new user %s\n", ent->client->pers.netname);

		ent->client->pers.loggedin = true;
		ApplyMax(ent);
		strncpy(ent->client->pers.skills.password + 16, ent->client->pers.netname, 16);
		saveCharacter(ent);
		return 1;
	}
    else    // Character file already exists
    {
		gi.cprintf(ent, PRINT_HIGH, "Character already exists. Please choose another name.\n");
		ent->client->pers.loggedin = false;
		ApplyMax(ent);
		return 0;
	}
}

int loadCharacter(edict_t *ent, char *password) {
	FILE *file = NULL;
	char path[128];
	char hashedPass[16];
	int test=120, i;

	if (!ent->client)
		return 0;

	if (!checkName(ent, ent->client->pers.netname))
		return 0;

	createNewSkills(ent, 0);
	sprintf(path, "%s/%s.ccs", charpath->string, ent->client->pers.netname);
	file = fopen(path, "rb");

	if (file == NULL)
    {
		gi.cprintf(ent, PRINT_HIGH, "No such character, use \"Create character\"\n");
		createNewSkills(ent, 0);
		ent->client->pers.loggedin = false;
		ApplyMax(ent);
		return 0;
	}

    // Unused coop stuff
	fread(&test, sizeof(coop->value), 1, file);
	if (test != coop->value)
    {
		if (!test)
			gi.cprintf(ent, PRINT_HIGH, "This character may not be used in cooperative mode\n");
		else
			gi.cprintf(ent, PRINT_HIGH, "This character may only be used in cooperative mode\n");
		createNewSkills(ent, 0);
		ent->client->pers.loggedin = false;
		fclose(file);
		ApplyMax(ent);
		return 0;
	}

    // Check valid password
	fread(&ent->client->pers.skills, sizeof(skills_t), 1, file);
    hashPassword(password, hashedPass);

    //gi.cprintf(ent, PRINT_HIGH, "Stored hash: %s\n", ent->client->pers.skills.password);
    //gi.cprintf(ent, PRINT_HIGH, "Enterd hash: %s\n", hashedPass);

	if (memcmp(ent->client->pers.skills.password, hashedPass, 15))
    {
		char msg[128];
		sprintf(msg, "%s failed login attempt.\n", ent->client->pers.netname);
		logmsg(msg);
		gi.cprintf(ent, PRINT_HIGH, "Wrong password\n");
		createNewSkills(ent, 0);
		ent->client->pers.loggedin = false;
		fclose(file);
		ApplyMax(ent);
		return 0;
	}

    // Successful login
	fread(ent->client->pers.inventory, sizeof(ent->client->pers.inventory), 1, file);
	ent->client->pers.loggedin = true;
	fclose(file);
	ApplyMax(ent);
	ent->health = ent->max_health;
	ent->client->magic = ent->client->max_magic;


// Check for bad powerups
// in Stash

/*
	for (i = 0; i < GIEX_PUCARRYPERCHAR; i++) {
		powerupinfo_t *puinfo;
		if (ent->client->pers.skills.powerup_type[i] == 0) {
			break;
		}
		puinfo = getPowerupInfo(ent->client->pers.skills.powerup_type[i]);
		if (!puinfo->inuse) {
			break;
		}
		if (ent->client->pers.skills.powerup_level[i] > puinfo->maxlevel) {
			gi.dprintf("lowering %s (%d in stash)\n", puinfo->name, i);
			ent->client->pers.skills.powerup_level[i] = puinfo->maxlevel;
		}
	}

// in Memory
	for (i = 0; i < GIEX_PUPERCHAR; i++) {
		powerupinfo_t *puinfo;
		if (ent->client->pers.skills.putype[i] == 0) {
			break;
		}
		puinfo = getPowerupInfo(ent->client->pers.skills.putype[i]);
		if (!puinfo->inuse) {
		   break;
		}
		if (puinfo->isspell < 1) {
			ent->client->pers.skills.putype[i] = 0;
			ent->client->pers.skills.pucurlvl[i] = 0;
			ent->client->pers.skills.pumaxlvl[i] = 0;
			ent->client->pers.skills.puexp[i] = 0;
			gi.dprintf("killing %s (%d in memory)\n", puinfo->name, i);
			continue;
		}*
		if (ent->client->pers.skills.pucurlvl[i] > puinfo->maxlevel) {
			ent->client->pers.skills.pucurlvl[i] = puinfo->maxlevel;
			gi.dprintf("lowering curlvl for %s (%d in memory)\n", puinfo->name, i);
		}
		if (ent->client->pers.skills.pumaxlvl[i] > puinfo->maxlevel) {
			ent->client->pers.skills.pumaxlvl[i] = puinfo->maxlevel;
			gi.dprintf("lowering maxlvl for %s (%d in memory)\n", puinfo->name, i);
		}
	}

// in Items
	for (i = 0; i < GIEX_ITEMPERCHAR; i++) {
		iteminfo_t *iteminfo;
		if (ent->client->pers.skills.itemId[i] == 0) {
			break;
		}
		iteminfo = getItemInfo(ent->client->pers.skills.itemId[i]);
		if (iteminfo->name[0] == '\0') {
			break;
		}
		for (pu = 0; pu < GIEX_PUPERITEM; pu++) {
			powerupinfo_t *puinfo;
			int puinfoslot;
			if (ent->client->pers.skills.item_putype[i][pu] == 0) {
				break;
			}
			puinfo = getPowerupInfo(ent->client->pers.skills.item_putype[i][pu]);
			if (!puinfo->inuse) {
				break;
			}
			puinfoslot = getItemPowerupInfoSlot(iteminfo, ent->client->pers.skills.item_putype[i][pu]);
			if (puinfoslot < 0) { // Incompatible powerup socketed
				ent->client->pers.skills.item_putype[i][pu] = 0;
				ent->client->pers.skills.item_pucurlvl[i][pu] = 0;
				ent->client->pers.skills.item_pumaxlvl[i][pu] = 0;
				ent->client->pers.skills.item_puexp[i][pu] = 0;
				gi.dprintf("killing %s in %s\n", puinfo->name, iteminfo->name);
			}
			if (ent->client->pers.skills.item_pucurlvl[i][pu] > puinfo->maxlevel + iteminfo->pumaxlvl[puinfoslot]) {
				ent->client->pers.skills.item_pucurlvl[i][pu] = puinfo->maxlevel + iteminfo->pumaxlvl[puinfoslot];
				gi.dprintf("lowering curlvl for %s in %s\n", puinfo->name, iteminfo->name);
			}
			if (ent->client->pers.skills.item_pumaxlvl[i][pu] > puinfo->maxlevel + iteminfo->pumaxlvl[puinfoslot]) {
				ent->client->pers.skills.item_pumaxlvl[i][pu] = puinfo->maxlevel + iteminfo->pumaxlvl[puinfoslot];
				gi.dprintf("lowering maxlvl for %s in %s\n", puinfo->name, iteminfo->name);
			}
		}
	}
*/

    //Check sanity of worn weapon
	if (ent->client->pers.skills.wornItem[0] == -1)
    {
		for (i = 0; i < GIEX_ITEMPERCHAR; i++)
        {
			iteminfo_t *iteminfo = getItemInfo(ent->client->pers.skills.itemId[i]);
			if ((iteminfo->type & 255) == GIEX_ITEM_WEAPON)
            {
				ent->client->pers.skills.wornItem[0] = i;
				break;
			}
		}
	}

    //Only re-equip weapon.
    /*	for (i = 0; i < 1; i++) {
		ent->client->pers.skills.activatingItem[i] = ent->client->pers.skills.wornItem[i]; //Make him re-wield everything
		ent->client->pers.skills.wornItem[i] = -1;
		updateItemLevels(ent);
	}*/

	updateItemLevels(ent);

    //Recalculate all exp requirements
	ent->client->pers.expRemain = getClassExpLeft(ent, ent->client->pers.skills.activeClass);
	for (i = 0; i < GIEX_PUPERCHAR; i++)
    {
		if (ent->client->pers.skills.putype[i] == 0)
			break;

		ent->client->pers.puexpRemain[i] = getPowerupCost(ent, i);
	}
	for (i = 0; i < GIEX_ITEMPERCHAR; i++)
    {
		int pu;
		if (ent->client->pers.skills.itemId[i] == 0)
			break;

		for (pu = 0; pu < GIEX_PUPERITEM; pu++)
        {
			if (ent->client->pers.skills.item_putype[i][pu] == 0)
				break;

			ent->client->pers.item_puexpRemain[i][pu] = getItemPowerupCost(ent, i, pu);
		}
	}
	for (i = 0; i < GIEX_BASEITEMS; i++)
    {
		ent->client->pers.skills.activatingItem[i] = -1;
	}
	ent->client->pers.itemchanging = -1; // set client ready to equip items

	strncpy(ent->client->pers.skills.password + 16, ent->client->pers.netname, 16);
	return 1;
}

void saveCharacter(edict_t *ent)
{
	FILE *file;
	char path[128];

	if (!ent->client)
		return;
	if (!ent->client->pers.loggedin) {
		gi.cprintf(ent, PRINT_HIGH, "You are not logged in!\n");
		return;
	}
	if (!checkName(ent, ent->client->pers.skills.password + 16)) {
		return;
	}

	gi.cprintf(ent, PRINT_HIGH, "Saving character \"%s\".\n", ent->client->pers.skills.password + 16);
	sprintf(path, "%s/%s.ccs", charpath->string, ent->client->pers.skills.password + 16);
	if ((file = fopen(path, "wb")) == NULL)
		return;
	if (coop->value) {
		int tmp=1;
		fwrite(&tmp, sizeof(int), 1, file);
	} else {
		int tmp=0;
		fwrite(&tmp, sizeof(int), 1, file);
	}
	fwrite(&ent->client->pers.skills, sizeof(skills_t), 1, file);
	fwrite(ent->client->pers.inventory, sizeof(ent->client->pers.inventory), 1, file);
	fclose(file);
}



// Reads a mapname.sco file and fills the outScores struct with the file data (max 10 entries in the list)
// Guarentees: does not modify mapname
//
void GiexGetSavedLevelHighscores(char* mapname, level_highscores_t* outScores)
{
    FILE *file = NULL;
    char path[128];
    sprintf(path, "%s/%s.sco", scorespath->string, mapname);
    file = fopen(path, "r");

    // Return early if the file does not exist (or some other error in opening)
    outScores->playerListSize = 0;
    if (file == NULL)
        return;

    // A quick test to see if the highscores file is empty for some reason
    fseek(file, 0, SEEK_SET);
    fgetc(file);
    if (feof(file))
    {
        fclose(file);
        return;
    }

    // Now we know our file is not empty, so read all of the rows into the struct
    fseek(file, 0, SEEK_SET);
    int i = 0;
    while (1)
    {
        fscanf(file, "%s", outScores->playerList[i].playerName);
        fscanf(file, "%d", &outScores->playerList[i].playerLevel);
        fscanf(file, "%lld", &outScores->playerList[i].timestamp);
        fscanf(file, "%d", &outScores->playerList[i].totalMonsterKills);
        fscanf(file, "%d", &outScores->playerList[i].totalPlayerKills);
        outScores->playerListSize++;
        i++;

        if (feof(file) || i >= 10)
            break;
    }
    fclose(file);
}


// Writes up to the first 10 entries in the scores struct to a mapname.sco file
// We assume that scores is sorted by totalMonsterKills (row 0 is highest number of kills)
// Guarentees: does not modify mapname and scores
//
void GiexWriteLevelHighscoresToFile(char* mapname, level_highscores_t* scores)
{
    FILE *file = NULL;
    char path[128];

    // If someone creates a map called giexg10highscores, don't overwrite our overall highscores file
    if (strncmp(mapname, "giexg10highscores", 17) == 0)
        return;

    sprintf(path, "%s/%s.sco", scorespath->string, level.mapname);
    file = fopen(path, "w"); // creates file if necessary, and clears file

    if (file == NULL)
        return;

    // Format of the highscores file is as follows:
    // Line 1: playername TAB playerlevel TAB date TAB monsterkills TAB playerkills
    // ...
    // Line 10: playername TAB playerlevel TAB date TAB monsterkills TAB playerkills
    fseek(file, 0, SEEK_SET);
    int count = scores->playerListSize;
    if (count > 10)
        count = 10;
    for (int i = 0; i < count; ++i)
    {
        fprintf(file, "%s\t", scores->playerList[i].playerName);
        fprintf(file, "%d\t", scores->playerList[i].playerLevel);
        fprintf(file, "%lld\t", scores->playerList[i].timestamp);
        fprintf(file, "%d\t", scores->playerList[i].totalMonsterKills);
        fprintf(file, "%d", scores->playerList[i].totalPlayerKills);
        if (i + 1 < count)
            fprintf(file, "\n"); // only write a newline if we are not the last entry
    }
    fclose(file);
}


// Given two highscores lists s1 and s2, merges them together and creates a sorted outScores list (row 0 is highest monsterkills)
// The input lists can each hold 20 entries, and the output can only hold 20 entries
// So it is possible that some values will not make it to the top 20 of the outScores list
// This is the current desired behavior because we only care about the top 10 really
// Guarentees: does not modify s1 and s2
//
void GiexMergeHighscores(level_highscores_t* s1, level_highscores_t* s2, level_highscores_t* outScores)
{
    outScores->playerListSize = 0;

    // Algorithm:
    // Step 1: Traverse both s1 and s2, find the largest monster kills
    // Step 2: Copy that entry into outScores
    // Step 3: Mark the entry in s1/s2 used
    // Step 4: Goto step 1 and repeat until outScores is full or all of s1/s2 used

    // The trick here is to combine S1 and S2 to make the search for the max really easy
    int merged[40] = {-1};
    for (int i = 0; i < s1->playerListSize; ++i)
        merged[i] = s1->playerList[i].totalMonsterKills;
    for (int i = 0; i < s2->playerListSize; ++i)
        merged[i + 20] = s2->playerList[i].totalMonsterKills;

    // Find max, copy entry, repeat till done
    // If two values for max are the same, we want to compare by timestamps
    while (1)
    {
        int maxNumber = -1;
        int index = -1;
        time_t timestamp = LLONG_MAX;
        for (int i = 0; i < 40; ++i)
        {
            // Make sure the value is > 0 so that we only use valid entries
            if (merged[i] > maxNumber && merged[i] > 0)
            {
                maxNumber = merged[i];
                index = i;
                if (i < 20)
                    timestamp = s1->playerList[i].timestamp;
                else
                    timestamp = s2->playerList[i - 20].timestamp;
            }
            else if (merged[i] == maxNumber && merged[i] > 0) // If equal, favor the oldest
            {
                time_t compareTimestamp;
                if (i < 20)
                    compareTimestamp = s1->playerList[i].timestamp;
                else
                    compareTimestamp = s2->playerList[i - 20].timestamp;

                if (compareTimestamp < timestamp)
                {
                    timestamp = compareTimestamp;
                    index = i;
                    maxNumber = merged[i];
                }
            }
        } // end for loop

        // If we didn't find a valid max number or do not have any output space, we are done
        if (maxNumber <= 0 || index < 0 || outScores->playerListSize >= 20)
            break;

        // We have a valid max number, so update outScores, and mark as used
        int saveI = outScores->playerListSize;
        if (index < 20)
        {
            strncpy(outScores->playerList[saveI].playerName, s1->playerList[index].playerName, 16);
            outScores->playerList[saveI].playerLevel = s1->playerList[index].playerLevel;
            outScores->playerList[saveI].timestamp = s1->playerList[index].timestamp;
            outScores->playerList[saveI].totalMonsterKills = s1->playerList[index].totalMonsterKills;
            outScores->playerList[saveI].totalPlayerKills = s1->playerList[index].totalPlayerKills;
        }
        else
        {
            strncpy(outScores->playerList[saveI].playerName, s2->playerList[index - 20].playerName, 16);
            outScores->playerList[saveI].playerLevel = s2->playerList[index - 20].playerLevel;
            outScores->playerList[saveI].timestamp = s2->playerList[index - 20].timestamp;
            outScores->playerList[saveI].totalMonsterKills = s2->playerList[index - 20].totalMonsterKills;
            outScores->playerList[saveI].totalPlayerKills = s2->playerList[index - 20].totalPlayerKills;
        }
        outScores->playerListSize++;
        merged[index] = -1; // marks item in list as used

    } // end while loop
}