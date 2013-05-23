#include "uirenderpreview.h"

UiRenderPreview::UiRenderPreview(QWidget *parent, QGLWidget *shared) :
    QGLWidget(QGLFormat(QGL::DoubleBuffer | QGL::DirectRendering), parent, shared) {
    setFocusPolicy(Qt::StrongFocus);
    render = 0;
}

void UiRenderPreview::initializeGL() {
    //OpenGL options
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    glHint(GL_PERSPECTIVE_CORRECTION_HINT,  GL_NICEST);
    glHint(GL_POINT_SMOOTH_HINT,            GL_NICEST);
    glHint(GL_LINE_SMOOTH_HINT,             GL_NICEST);
    glHint(GL_POLYGON_SMOOTH_HINT,          GL_NICEST);
}

void UiRenderPreview::resizeGL(int width, int height) {
    glViewport(0, 0, (GLint)width, (GLint)height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 1, 0, 1, 1, -1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void UiRenderPreview::paintPreview(NxEventsPropagation *_render, GLuint _renderPreviewTexture, QSizeF _renderSize) {
    render               = _render;
    renderSize           = _renderSize;
    renderPreviewTexture = _renderPreviewTexture;
    updateGL();
}

void UiRenderPreview::paintGL() {
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    qreal scaleX = 1, scaleY = 1;
    qreal ratioRender  = (qreal)width()            / (qreal)height();
    qreal ratioTexture = (qreal)renderSize.width() / (qreal)renderSize.height();

    if(ratioRender >= ratioTexture) scaleX = ratioTexture / ratioRender;
    else                            scaleY = ratioRender  / ratioTexture;

    glPushMatrix();
    glTranslatef((1-scaleX)/2, (1-scaleY)/2, 0);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, renderPreviewTexture);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);    glVertex3f(0,      0,      0);
    glTexCoord2f(1, 0);    glVertex3f(scaleX, 0,      0);
    glTexCoord2f(1, 1);    glVertex3f(scaleX, scaleY, 0);
    glTexCoord2f(0, 1);    glVertex3f(0,      scaleY, 0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}
