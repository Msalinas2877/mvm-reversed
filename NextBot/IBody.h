/* reverse engineering by sigsegv
 * based on TF2 version 20151007a
 * NextBot: body component
 */


class IBody : public INextBotComponent
{
public:
	enum class LookAtPriorityType : int
	{
		BORING      = 0,
		INTERESTING = 1,
		IMPORTANT   = 2,
		CRITICAL    = 3,
	};
	
	enum class PostureType : int
	{
		// TODO
		CROUCH = 1,
		// TODO
	};
	
	enum class ArousalType : int
	{
		// TODO
	};
	
	IBody(INextBot *nextbot);
	virtual ~IBody();
	
	virtual void Reset() override;
	virtual void Update() override;
	
	virtual bool SetPosition(const Vector& pos);
	virtual Vector& GetEyePosition() const;
	virtual Vector& GetViewVector() const;
	virtual void AimHeadTowards(const Vector& vec, LookAtPriorityType priority, float duration, INextBotReply *reply, const char *s1);
	virtual void AimHeadTowards(CBaseEntity *ent, LookAtPriorityType priority, float duration, INextBotReply *reply, const char *s1);
	virtual bool IsHeadAimingOnTarget() const;
	virtual bool IsHeadSteady() const;
	virtual float GetHeadSteadyDuration() const;
	virtual float GetHeadAimSubjectLeadTime() const;
	virtual float GetHeadAimTrackingInterval() const;
	virtual void ClearPendingAimReply();
	virtual float GetMaxHeadAngularVelocity() const;
	virtual bool StartActivity(Activity a1, unsigned int i1);
	virtual int SelectAnimationSequence(Activity a1) const;
	virtual Activity GetActivity() const;
	virtual bool IsActivity(Activity a1) const;
	virtual bool HasActivityType(unsigned int i1) const;
	virtual void SetDesiredPosture(PostureType posture);
	virtual PostureType GetDesiredPosture() const;
	virtual bool IsDesiredPosture(PostureType posture) const;
	virtual bool IsInDesiredPosture() const;
	virtual PostureType GetActualPosture() const;
	virtual bool IsActualPosture(PostureType posture) const;
	virtual bool IsPostureMobile() const;
	virtual bool IsPostureChanging() const;
	virtual void SetArousal(ArousalType arousal);
	virtual ArousalType GetArousal() const;
	virtual bool IsArousal(ArousalType arousal) const;
	virtual float GetHullWidth() const;
	virtual float GetHullHeight() const;
	virtual float GetStandHullHeight() const;
	virtual float GetCrouchHullHeight() const;
	virtual Vector& GetHullMins() const;
	virtual Vector& GetHullMaxs() const;
	virtual unsigned int GetSolidMask() const;
	virtual int GetCollisionGroup() const;
};


class CHeadlessHatmanBody : public IBody
{
	// TODO
};


class CMerasmusBody : public IBody
{
	// TODO
};


class CTFTankBossBody : public IBody
{
	// TODO
};


class CBotNPCBody : public IBody
{
	// TODO
};

class CEyeballBossBody : public CBotNPCBody
{
	// TODO
};


class PlayerBody : public IBody
{
	// TODO
};

// sizeof: 0xc8
class CTFBotBody : public PlayerBody
{
	// TODO
};