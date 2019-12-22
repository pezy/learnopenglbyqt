#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QVector>

QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)
QT_FORWARD_DECLARE_CLASS(QOpenGLTexture)
QT_FORWARD_DECLARE_CLASS(QOpenGLVertexArrayObject)
QT_FORWARD_DECLARE_CLASS(QOpenGLBuffer)

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT

 public:
  explicit GLWidget(QWidget* parent = 0);
  ~GLWidget();

 protected:
  void initializeGL() override;
  void paintGL() override;
  void resizeGL(int w, int h) override;

 private:
  void CreateTriangle();

 private:
  QOpenGLTexture* texture_ = nullptr;
  QVector<QOpenGLShaderProgram*> programs_;
  QVector<QOpenGLVertexArrayObject*> vaos_;
  QVector<QOpenGLBuffer*> vbos_;
  // QOpenGLBuffer ebo_;
};

#endif  // GLWIDGET_H
