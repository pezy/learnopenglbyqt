#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>

QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)
QT_FORWARD_DECLARE_CLASS(QOpenGLTexture)

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
  QOpenGLShaderProgram* program_ = nullptr;
  QOpenGLBuffer vbo_;
};

#endif  // GLWIDGET_H
