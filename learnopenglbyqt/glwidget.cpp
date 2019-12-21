#include "glwidget.h"

#include <QDebug>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QVector>

GLWidget::GLWidget(QWidget *parent)
    : QOpenGLWidget(parent), vbo_(QOpenGLBuffer::VertexBuffer) {}

GLWidget::~GLWidget() {
  makeCurrent();
  vbo_.destroy();
  delete texture_;
  delete program_;
  doneCurrent();
}

void GLWidget::initializeGL() {
  initializeOpenGLFunctions();

  CreateTriangle();

  program_ = new QOpenGLShaderProgram;
  program_->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vertex.glsl");
  program_->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/frag.glsl");
  program_->link();
  program_->bind();

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
  glEnableVertexAttribArray(0);

  glClear(GL_COLOR_BUFFER_BIT);
  glClearColor(0.2f, 0.3f, 0.3f, 1.f);

  qDebug() << program_->log();
}

void GLWidget::paintGL() {
  glDrawArrays(GL_TRIANGLES, 0, 3);
  glFlush();
}

void GLWidget::resizeGL(int w, int h) { glViewport(0, 0, w, h); }

void GLWidget::CreateTriangle() {
  const QVector<GLfloat> vertices{-0.5f, -0.5f, 0.0f, 0.5f, -0.5f,
                                  0.0f,  0.0f,  0.5f, 0.0f};
  vbo_.create();
  vbo_.setUsagePattern(QOpenGLBuffer::StaticDraw);
  vbo_.bind();
  vbo_.allocate(vertices.constData(), vertices.count() * sizeof(GLfloat));
}
