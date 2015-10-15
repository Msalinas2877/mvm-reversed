/* reverse engineering by sigsegv
 * based on server_srv.so version 20151006
 * Population: spawners
 */


// TODO: type name for this?
enum {
	BOT_ATTRIBUTES_REMOVEONDEATH           = (1 << 0),
	BOT_ATTRIBUTES_AGGRESSIVE              = (1 << 1),
	// 4?
	BOT_ATTRIBUTES_SUPPRESSFIRE            = (1 << 3),
	BOT_ATTRIBUTES_DISABLEDODGE            = (1 << 4),
	BOT_ATTRIBUTES_BECOMESPECTATORONDEATH  = (1 << 5),
	// 6?
	BOT_ATTRIBUTES_RETAINBUILDINGS         = (1 << 7),
	BOT_ATTRIBUTES_SPAWNWITHFULLCHARGE     = (1 << 8),
	BOT_ATTRIBUTES_ALWAYSCRIT              = (1 << 9),
	BOT_ATTRIBUTES_IGNOREENEMIES           = (1 << 10),
	BOT_ATTRIBUTES_HOLDFIREUNTILFULLRELOAD = (1 << 11),
	// 12?
	BOT_ATTRIBUTES_ALWAYSFIREWEAPON        = (1 << 13),
	BOT_ATTRIBUTES_TELEPORTTOHINT          = (1 << 14),
	BOT_ATTRIBUTES_MINIBOSS                = (1 << 15),
	BOT_ATTRIBUTES_USEBOSSHEALTHBAR        = (1 << 16),
	BOT_ATTRIBUTES_IGNOREFLAG              = (1 << 17),
	BOT_ATTRIBUTES_AUTOJUMP                = (1 << 18),
	BOT_ATTRIBUTES_AIRCHARGEONLY           = (1 << 19),
	BOT_ATTRIBUTES_VACCINATORBULLETS       = (1 << 20),
	BOT_ATTRIBUTES_VACCINATORBLAST         = (1 << 21),
	BOT_ATTRIBUTES_VACCINATORFIRE          = (1 << 22),
	BOT_ATTRIBUTES_BULLETIMMUNE            = (1 << 23),
	BOT_ATTRIBUTES_BLASTIMMUNE             = (1 << 24),
	BOT_ATTRIBUTES_FIREIMMUNE              = (1 << 25),
	
	
	BOT_RESTRICT_MELEEONLY     = (1 << 0),
	BOT_RESTRICT_PRIMARYONLY   = (1 << 1),
	BOT_RESTRICT_SECONDARYONLY = (1 << 2),
	
	
	BOT_SKILL_EASY   = 0,
	BOT_SKILL_NORMAL = 1,
	BOT_SKILL_HARD   = 2,
	BOT_SKILL_EXPERT = 3,
};


/* sizeof: ??? */
struct CTFBot::EventChangeAttributes_t
{
	CUtlString ???              // +0x00
	int m_iSkill;               // +0x04
	int m_nWeaponRestrict;      // +0x08
	// TODO: 0x0c
	// TODO: 0x10
	int m_nAttributes;          // +0x14
	float m_flVisionRange;      // +0x18
	CUtlStringList m_ItemNames; // +0x1c
	// TODO: 0x2c
	CUtlVector<CTFBot::EventChangeAttributes_t::item_attributes_t> m_ItemAttrs; // +0x30
	// TODO: 0x40
	CUtlVector<static_attrib_t> m_CharAttrs; // +0x44
	// TODO: 0x54
	CUtlStringList m_Tags;  // +0x58
	// TODO: 0x68
	// ...
};


class IPopulationSpawner
{
public:
	virtual ~IPopulationSpawner() {}
	
	virtual bool Parse(KeyValues *kv) = 0;
	virtual bool Spawn(const Vector&, CUtlVector<CHandle<CBaseEntity>>, int) = 0;
	virtual bool IsWhereRequired();
	virtual bool IsVarious();
	virtual int GetClass(int index);
	virtual string_t GetClassIcon(int);
	virtual int GetHealth(int);
	virtual bool IsMiniBoss(int);
	virtual bool HasAttribute(CTFBot::AttributeType attr, int index);
	virtual bool HasEventChangeAttributes(const char *name) const = 0;
	
	static IPopulationSpawner *ParseSpawner(IPopulator *populator, KeyValues *kv);
	
protected:
	IPopulator *m_Populator; // +0x04
};


class CMobSpawner : public IPopulationSpawner
{
public:
	CMobSpawner(IPopulator *populator);
	virtual ~CMobSpawner();
	
	virtual bool Parse(KeyValues *kv);
	virtual bool Spawn(const Vector&, CUtlVector<CHandle<CBaseEntity>>, int);
	virtual bool HasEventChangeAttributes(const char *name) const;
	
private:
	int                 m_iCount;     // +0x08
	IPopulationSpawner *m_SubSpawner; // +0x0c
	// TODO
};


class CSentryGunSpawner : public IPopulationSpawner
{
public:
	CSentryGunSpawner(IPopulator *populator);
	virtual ~CSentryGunSpawner();
	
	virtual bool Parse(KeyValues *kv);
	virtual bool Spawn(const Vector&, CUtlVector<CHandle<CBaseEntity>>, int);
	virtual bool HasEventChangeAttributes(const char *name) const;
	
private:
	int m_iLevel; // +0x08
};


class CTankSpawner : public IPopulationSpawner
{
public:
	CTankSpawner(IPopulator *populator);
	virtual ~CTankSpawner();
	
	virtual bool Parse(KeyValues *kv);
	virtual bool Spawn(const Vector&, CUtlVector<CHandle<CBaseEntity>>, int);
	virtual bool IsWhereRequired();
	virtual string_t GetClassIcon(int);
	virtual int GetHealth(int);
	virtual bool IsMiniBoss();
	virtual bool HasEventChangeAttributes(const char *name) const;
	
private:
	int        m_iHealth;             // +0x08
	float      m_flSpeed;             // +0x0c
	CUtlString m_strName;             // +0x10
	CUtlString m_strStartNode;        // +0x14
	int        m_iSkin;               // +0x18
	Event     *m_OnKilledOutput;      // +0x1c
	Event     *m_OnBombDroppedOutput; // +0x20
};


class CTFBotSpawner : public IPopulationSpawner
{
public:
	CTFBotSpawner(IPopulator *populator);
	virtual ~CTFBotSpawner();
	
	virtual bool Parse(KeyValues *kv);
	virtual bool Spawn(const Vector&, CUtlVector<CHandle<CBaseEntity>>, int);
	virtual int GetClass(int index);
	virtual string_t GetClassIcon(int);
	virtual int GetHealth(int);
	virtual bool IsMiniBoss();
	virtual bool HasAttribute(CTFBot::AttributeType attr, int index);
	virtual bool HasEventChangeAttributes(const char *name) const;
	
	bool ParseEventChangeAttributes(KeyValues *kv);
	
private:
	// TODO 0x04
	int m_iClass;               // +0x08
	const char *m_strClassIcon; // +0x0c
	int m_iHealth;              // +0x10
	float m_flScale;            // +0x14
	float m_flAutoJumpMin;      // +0x18
	float m_flAutoJumpMax;      // +0x1c
	// TODO 0x20: CUtlString
	// TODO 0x24: CUtlString
	// TODO 0x28
	// TODO 0x2c
	// TODO 0x30
	// TODO 0x34
	// TODO 0x38: CUtlString
	// TODO 0x3c
	// TODO 0x40
	// TODO 0x44
	// TODO 0x48
	// TODO 0x4c
	// TODO 0x50
	// TODO 0x54: CUtlStringList (sizeof: 0x14)
	CUtlVector<CTFBot::EventChangeAttributes_t> m_Attrs; // +0x68
	// TODO 0x78
	CUtlVector<static_attrib_t> m_StaticAttrs; // +0x7c
	// TODO 0x8c
	// TODO 0x90: CUtlStringList (sizeof: 0x14)
	CUtlVector<CTFBot::EventChangeAttributes_t::item_attributes_t> m_ItemAttrs; // +0xa4
	// TODO 0xb4
};


class CSquadSpawner : public IPopulationSpawner
{
public:
	CSquadSpawner(IPopulator *populator);
	virtual ~CSquadSpawner();
	
	virtual bool Parse(KeyValues *kv);
	virtual bool Spawn(const Vector&, CUtlVector<CHandle<CBaseEntity>>, int);
	virtual bool IsVarious();
	virtual int GetClass(int index);
	virtual string_t GetClassIcon(int);
	virtual int GetHealth(int);
	virtual bool IsMiniBoss();
	virtual bool HasAttribute(CTFBot::AttributeType attr, int index);
	virtual bool HasEventChangeAttributes(const char *name) const;
	
private:
	// TODO
};


class CRandomChoiceSpawner : public IPopulationSpawner
{
public:
	CRandomChoiceSpawner(IPopulator *populator);
	virtual ~CRandomChoiceSpawner();
	
	virtual bool Parse(KeyValues *kv);
	virtual bool Spawn(const Vector&, CUtlVector<CHandle<CBaseEntity>>, int);
	virtual bool IsVarious();
	virtual int GetClass(int index);
	virtual string_t GetClassIcon(int);
	virtual int GetHealth(int);
	virtual bool IsMiniBoss();
	virtual bool HasAttribute(CTFBot::AttributeType attr, int index);
	virtual bool HasEventChangeAttributes(const char *name) const;
	
private:
	// TODO
};


bool ParseDynamicAttributes(CTFBot::EventChangeAttributes_t& attr, KeyValues *kv);
