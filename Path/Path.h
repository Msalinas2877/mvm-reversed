/* reverse engineering by sigsegv
 * based on TF2 version 20151007a
 * Pathfinding: path
 */


class IPathOpenGoalSelector
{
public:
	virtual CNavArea *operator()(CNavArea *area1, CNavArea *area2) const;
};


class Path
{
public:
	enum class SegmentType : int
	{
		// TODO
	};
	
	enum class SeekType : int
	{
		// TODO
	};
	
	enum class MoveCursorType : int
	{
		ABSOLUTE = 0,
		RELATIVE = 1,
	};
	
	enum class ResultType : int
	{
		// TODO
	};
	
	struct Segment
	{
		// 00 pointer to something with:
		//    - sizeof >= 0x58
		//    - bitfield at +0x54
		// 04 ?
		
		Vector m_vecStart;   // +0x08 coordinates of the start of this segment
		
		// 14 pointer to something with:
		//    00 Vector
		//    0c Vector
		//    ...?
		
		SegmentType m_Type;  // +0x18
		
		// 1c Vector, accessed in Draw
		
		float m_flLength;    // +0x28 length of this segment
		float m_flStartDist; // +0x2c distance from the start of the path to the start of this segment
		
		// 30 float, might possibly be negative sometimes perhaps?
		// 34 ?
		// 38 ?
		// 3c ?
		// 40 ?
	};
	
	struct CursorData
	{
		// 00 Vector: Segment::m_vecStart
		// 0c Vector: Segment+1c
		// 18 float:  Segment+30
		Segment *m_pSegment; // +0x1c
	};
	
	Path();
	virtual ~Path();
	
	virtual float GetLength() const;
	
	virtual const Vector& GetPosition(float dist, const Segment *seg) const;
	virtual const Vector& GetClosestPosition(const Vector& v1, const Segment *seg, float f1) const;
	virtual const Vector& GetStartPosition() const;
	virtual const Vector& GetEndPosition() const;
	
	virtual CBaseEntity *GetSubject() const;
	virtual const Segment *GetCurrentGoal() const;
	virtual float GetAge() const;
	
	virtual void MoveCursorToClosestPosition(const Vector&, SeekType stype, float f1) const;
	virtual void MoveCursorToStart();
	virtual void MoveCursorToEnd();
	virtual void MoveCursor(float dist, MoveCursorType mctype);
	
	virtual float GetCursorPosition() const;
	virtual CursorData *GetCursorData() const;
	
	virtual bool IsValid() const;
	virtual void Invalidate();
	
	virtual void Draw(const Segment *seg) const;
	virtual void DrawInterpolated(float from, float to);
	
	virtual const Segment *FirstSegment() const;
	virtual const Segment *NextSegment(const Segment *seg) const;
	virtual const Segment *PriorSegment(const Segment *seg) const;
	virtual const Segment *LastSegment() const;
	
	virtual void OnPathChanged(INextBot *nextbot, ResultType rtype);
	
	virtual void Copy(INextBot *nextbot, const Path& that);
	
	virtual bool ComputeWithOpenGoal(INextBot *nextbot, const IPathCost& cost, const IPathOpenGoalSelector& sel, float f1);
	virtual void ComputeAreaCrossing(INextBot *nextbot, const CNavArea *area, const Vector& from, const CNavArea *to, NavDirType dir, Vector *out) const;
	
	void AssemblePrecomputedPath(INextBot *nextbot, const Vector& v1, CNavArea *area);
	bool BuildTrivialPath(INextBot *nextbot, const Vector& v1);
	int FindNextOccludedNode(INextBot *nextbot, int index);
	void InsertSegment(Segment seg, int index);
	void Optimize(INextBot *nextbot);
	void PostProcess();
	
	template<class T> bool Compute(INextBot *nextbot, const Vector& v1, T&, float f1, bool b1);
	
protected:
	Segment m_Segments[256];         // +0x0004
	int m_iSegCount;                 // +0x4404
	Vector m_vecGetPosition;         // +0x4408
	Vector m_vecGetClosestPosition;  // +0x4414
	float m_flCursorPosition;        // +0x4420
	CursorData m_CursorData;         // +0x4424
	bool m_bCursorDataDirty;         // +0x4444
	IntervalTimer m_itAge;           // +0x4448
	CHandle<CBaseEntity> m_hSubject; // +0x444c
};
