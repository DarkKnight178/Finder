/*
	main.cpp
*/

#ifdef _DEBUG
	#include <vld.h>
#endif

#include "Model/CFinder.h"
#include "Controller/CController.h"
#include "View/Console/CConsoleView.h"


int main()
{
	DWORD _logMode = LM_CMD;
	const TCHAR* _logFileName = nullptr;
	CLogger* _logger = nullptr;

	#ifdef _DEBUG
		_logger = new CLogger(_logMode, _logFileName);
	#endif

	CFinder* _model = CFinder::GetInstance(_logger);
	CController* _controller = CController::GetInstance(*_model, _logger);
	CConsoleView* _view = CConsoleView::GetInstance(*_controller, _logger);
	_controller->SetView(*_view);

	_controller->Run();

	SAFE_DELETE(_view);
	SAFE_DELETE(_controller);
	SAFE_DELETE(_model);
	SAFE_DELETE(_logger);
	
	system("pause");
	return 0;
}