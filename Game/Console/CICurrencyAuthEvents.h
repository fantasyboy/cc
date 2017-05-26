// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装器类

#import "E:\\workspace\\cc\\Game\\Console\\res\\AllpurAuthentic.dll" no_namespace
// CICurrencyAuthEvents 包装器类

class CICurrencyAuthEvents : public COleDispatchDriver
{
public:
	CICurrencyAuthEvents() {} // 调用 COleDispatchDriver 默认构造函数
	CICurrencyAuthEvents(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CICurrencyAuthEvents(const CICurrencyAuthEvents& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// 特性
public:

	// 操作
public:


	// _ICurrencyAuthEvents 方法
public:
	void OnUpdate()
	{
		InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void OnInvalid()
	{
		InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void OnBulletin(LPCTSTR content)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, parms, content);
	}

	// _ICurrencyAuthEvents 属性
public:

};
