#include "CommandModelAdd.h"
#include "Model.h"
#include "ProcessingEngine.h"
#include "QVTKFramebufferObjectRenderer.h"


CommandModelAdd::CommandModelAdd(QVTKFramebufferObjectRenderer *vtkFboRenderer, std::shared_ptr<ProcessingEngine> processingEngine, QUrl modelPath)
	: CommandModel{vtkFboRenderer}
	, m_processingEngine{processingEngine}
	, m_modelPath{modelPath}
	, m_applyTransformations{false}
{
}

void CommandModelAdd::run()
{
	qDebug() << "CommandModelAdd::run()";

	m_model = m_processingEngine->addModel(m_modelPath);

	m_processingEngine->placeModel(m_model);

	m_ready = true;
	emit ready();
}


bool CommandModelAdd::isReady()
{
	return m_ready;
}

bool CommandModelAdd::addToStack()
{
	return m_addToStack;
}

void CommandModelAdd::undo()
{
	qDebug() << "CommandModelAdd::undo(): Delete the model";
}

void CommandModelAdd::redo()
{
	qDebug() << "CommandModelAdd::redo()";

	m_vtkFboRenderer->addModelActor(m_model);

	emit done();
}
