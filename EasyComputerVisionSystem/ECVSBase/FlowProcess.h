#pragma once
//////////////////////////////////////////////////////////////////////////
//
//	FlowProcess.h 2015-5-13 李春峰 
//   CFlowProcess 是流程处理类，所有的逻辑流程都在改类中进行
//   该类维护所有算法之间的数据交互,第一版本暂时只支持单个流程，
//   
//////////////////////////////////////////////////////////////////////////
class ECVS_EXPORT CFlowProcess
{
	friend class CInputSet;
private:
	//算法运行错误后处理流程
	enum RunFaildProcess
	{
		BREAK,   //直接停止运行
		IGNORED, //忽略
		STEPTO,  //跳转
	};
	//算法间输入输出之间的关系
	struct InputOutputRelateship  
	{
		string m_strWitchParam; //为算法的哪一个参数的关联值
		int nIndex;				//为关联到哪一个算法
		string m_strDestParam;  //取目标算法的哪一个字段
		vector<int>	m_vecIndex;  //取目标算法的哪些值，如果目标为非vector 该值为空，如果是序列按照该vector取值
	};

	struct  AlgrithmRelateship
	{
		vector<InputOutputRelateship*> m_relationShip;
		RunFaildProcess m_FalidProcess; //运行错误处理流程 默认停止运行
		int m_nStep2Index;				//如果是跳转，那么跳转到哪一步
		AlgrithmRelateship()
		{
			m_FalidProcess = RunFaildProcess::BREAK;
			m_nStep2Index = 0;
		}
		~AlgrithmRelateship()
		{
			DeleteMemory();
		}
		AlgrithmRelateship(const AlgrithmRelateship& rhs)
		{
			Copy(rhs);
		}
		const AlgrithmRelateship&operator = (const AlgrithmRelateship& rhs)
		{
			if (this != &rhs)
			{
				Copy(rhs);
			}
			return *this;
		}
	private:
		void DeleteMemory()
		{
			for (int i = m_relationShip.size() - 1; i >= 0; --i)
			{
				delete m_relationShip[i];
				m_relationShip[i] = NULL;
				m_relationShip.pop_back();
			}
		}
		void Copy(const AlgrithmRelateship& rhs)
		{
			DeleteMemory();
			m_FalidProcess = rhs.m_FalidProcess;
			m_nStep2Index = rhs.m_nStep2Index;
		}

	};
	

public:
	CFlowProcess();
	CFlowProcess(const CFlowProcess& rhs);
	const CFlowProcess& operator=(const CFlowProcess& rhs);
	~CFlowProcess();
	bool AddAlgrithm(CAlgrithmBase* pAlgrithm); //往集合最后添加一个算法
	bool SetAlgrithm(int nIndex); //对某一个算法进行设置，
	bool SetAlgrithmName(int nIndex, std::string strName); //设置算法显示名字
	bool InsertAlgirthm(CAlgrithmBase* pAlgrithm, int nIndex); //插入一个算法到nIndex处，如果超出范围 ,返回false，什么都不做
	bool ExchangeAlgrithmIndex(int nIndex1, int nIndex2); //将nIndex1和nIndex2的算法相互交换,下标不在范围返回false
	bool ChangeAlgrithmIndex(int nIndex, int nChangedIndex); //将nIndex的算法放到nChangedIndex处 之间的算法依次填补过去,下标非法返回错误
	bool DelAlgrithm(int nIndex); //删除nIndex处的Algorithm,如果下标非法则返回false

	bool ComplierFlow(string& strError);  //编译算法流程是否合法，数据交互的合法性,strError返回所有的错误
	bool  Run();  //开始执行流程
	int  GetAlgrithmNumber()
	{
		return m_pAlgrithms.size();
	}
	bool SetInput(int nIndex);
	
private: 
	vector<CAlgrithmBase*> m_pAlgrithms;   // 流程中的算法集合
	//vector< vector<AlgrithmRelateship*> >m_vecRalationSheep;  //算法间的相互关系
	vector<AlgrithmRelateship*> m_vecRalationSheep;  //算法间的相互关系
	vector< vector<CToolOutput*> >  m_pOutput; // 执行过程中每个算法的输出值



private:
	//设置第nIndex算法的输入参数
	void SetInputParam(int nIndex);

	//删除所有内存
	void DeleteMemory();
	void Copy(const CFlowProcess& rhs);

};

