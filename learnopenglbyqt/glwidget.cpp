#include "glwidget.h"

#include <QDebug>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLVertexArrayObject>
#include <QVector>

GLWidget::GLWidget(QWidget* parent) : QOpenGLWidget(parent) {
  programs_.resize(2);
  vaos_.resize(2);
  vbos_.resize(2);
}

GLWidget::~GLWidget() {
  makeCurrent();
  for (auto& vbo : vbos_) {
    vbo->destroy();
  }
  // ebo_.destroy();
  doneCurrent();
}

void GLWidget::initializeGL() {
  initializeOpenGLFunctions();

  glClearColor(0.2f, 0.3f, 0.3f, 1.f);

  programs_[0] = new QOpenGLShaderProgram(this);
  programs_[0]->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vertex.glsl");
  programs_[0]->addShaderFromSourceFile(QOpenGLShader::Fragment,
                                        ":/orange.glsl");
  programs_[0]->link();
  qDebug() << programs_[0]->log();

  programs_[1] = new QOpenGLShaderProgram(this);
  programs_[1]->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vertex.glsl");
  programs_[1]->addShaderFromSourceFile(QOpenGLShader::Fragment,
                                        ":/yellow.glsl");
  programs_[1]->link();
  qDebug() << programs_[1]->log();

  CreateTriangle();
}

void GLWidget::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT);

  programs_[0]->bind();

  vaos_[0]->bind();
  vbos_[0]->bind();
  programs_[0]->enableAttributeArray(0);
  programs_[0]->setAttributeBuffer(0, GL_FLOAT, 0, 3);
  glDrawArrays(GL_TRIANGLES, 0, 3);

  programs_[1]->bind();

  vaos_[1]->bind();
  vbos_[1]->bind();
  programs_[1]->enableAttributeArray(0);
  programs_[1]->setAttributeBuffer(0, GL_FLOAT, 0, 3);
  glDrawArrays(GL_TRIANGLES, 0, 3);

  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
  // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void GLWidget::resizeGL(int w, int h) { glViewport(0, 0, w, h); }

void GLWidget::CreateTriangle() {
  const QVector<GLfloat> vertices0{-0.9f, -0.5f,  0.0f, -0.0f, -0.5f,
                                   0.0f,  -0.45f, 0.5f, 0.0f};
  const QVector<GLfloat> vertices1{0.0f, -0.5f, 0.0f, 0.9f, -0.5f,
                                   0.0f, 0.45f, 0.5f, 0.0f};

  vaos_[0] = new QOpenGLVertexArrayObject(this);
  vaos_[0]->create();
  vaos_[0]->bind();

  vbos_[0] = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
  vbos_[0]->create();
  vbos_[0]->setUsagePattern(QOpenGLBuffer::StaticDraw);
  vbos_[0]->bind();
  vbos_[0]->allocate(vertices0.constData(), vertices0.size() * sizeof(GLfloat));

  vaos_[1] = new QOpenGLVertexArrayObject(this);
  vaos_[1]->create();
  vaos_[1]->bind();

  vbos_[1] = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
  vbos_[1]->create();
  vbos_[1]->setUsagePattern(QOpenGLBuffer::StaticDraw);
  vbos_[1]->bind();
  vbos_[1]->allocate(vertices1.constData(), vertices1.size() * sizeof(GLfloat));

  //  ebo_.create();
  //  ebo_.setUsagePattern(QOpenGLBuffer::StaticDraw);
  //  ebo_.bind();
  //  ebo_.allocate(indices.constData(), indices.count() * sizeof(uint));
}
