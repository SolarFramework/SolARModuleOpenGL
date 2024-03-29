/**
 * @copyright Copyright (c) 2017 B-com http://www.b-com.com/
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef SOLAR3DPOINTSVIEWEROPENGL_H
#define SOLAR3DPOINTSVIEWEROPENGL_H

#include <vector>

#include "api/display/I3DPointsViewer.h"

#include "SolAROpenglAPI.h"

#include "xpcf/component/ConfigurableBase.h"

#include "src/glcamera/gl_camera.hpp"

namespace SolAR {
namespace MODULES {
namespace OPENGL {

/**
 * @class SolAR3DPointsViewerOpengl
 * @brief <B>Displays in a window a set of 3D points as well as the current camera and its previous path (based on an OpenGL implementation).</B>
 * <TT>UUID: afd38ea0-9a46-11e8-9eb6-529269fb1459</TT>
 *
 * This component display a set of 3D points and the current camera as well as previous frames and keyframes. The view point is automatically define to be focus on the center of the point cloud and to show both the 3D points as well as the current camera.
 * The user can change this view point by left clicking and moving the mouse to turn around the point cloud or by right clicking and moving the mouse to move in translation.
 * Configuration parameters allow user to visualize the axis of the coordinate systems of the world, the center of the point cloud, and the camera.
 * The color of points can be fixed, or can be the one assigned to each point.
 * The scale of the points, camera and coordinate systems axis can be defined by the usr thanks to configuration parameters.
 *
 * @SolARComponentPropertiesBegin
 * @SolARComponentProperty{ title,
 *                          the title of the window on which the image will be displayed,
 *                          @SolARComponentPropertyDescString{ "" }}
 * @SolARComponentProperty{ width,
 *                          the width of the window on which the image will be displayed (if <=0\, the width of the input image),
 *                          @SolARComponentPropertyDescNum{ int, [0..MAX INT], 0 }}
 * @SolARComponentProperty{ height,
 *                          the height of the window on which the image will be displayed (if <=0\, the height of the input image),
 *                          @SolARComponentPropertyDescNum{ int, [0..MAX INT], 0 }}
 * @SolARComponentProperty{ backgroundColor,
 *                          background color,
 *                          @SolARComponentPropertyDescList{ 3, uint, [0..255], { 255\, 255\, 255 } }}
 * @SolARComponentProperty{ fixedPointsColor,
 *                          if 0, the color of each point is used\, else the color defined in parameter by user is used,
 *                          @SolARComponentPropertyDescNum{ uint, [0,1], 1 }}
 * @SolARComponentProperty{ pointsColor,
 *                          points color,
 *                          @SolARComponentPropertyDescList{ 3, uint, [0..255], { 0\, 255\, 0 } }}
 * @SolARComponentProperty{ points2Color,
 *                          points color for the second cloud,
 *                          @SolARComponentPropertyDescList{ 3, uint, [0..255], { 255\, 0\, 0 } }}
 * @SolARComponentProperty{ cameraColor,
 *                          camera color,
 *                          @SolARComponentPropertyDescList{ 3, uint, [0..255], { 0\, 0\, 255 } }}
 * @SolARComponentProperty{ keyframeAsCamera,
 *                          if not 0\, each keyframe pose is drawn as a camera\, else as a point,
 *                          @SolARComponentPropertyDescNum{ uint, [0\,1], 0 }}
 * @SolARComponentProperty{ framesColor,
 *                          frame color,
 *                          @SolARComponentPropertyDescList{ 3, uint, [0..255], { 180\, 180\, 180 } }}
 * @SolARComponentProperty{ keyframesColor,
 *                          keyframe color,
 *                          @SolARComponentPropertyDescList{ 3, uint, [0..255], { 0\, 255\, 0 } }}
 * @SolARComponentProperty{ keyframes2Color,
 *                          keyframe color for the second vector of keyframe,
 *                          @SolARComponentPropertyDescList{ 3, uint, [0..255], { 255\, 0\, 0 } }}
 * @SolARComponentProperty{ drawCameraAxis,
 *                          if not 0\, a gizmo showing the coordinate system of the camera is displayed,
 *                          @SolARComponentPropertyDescNum{ uint, [0\,1], 1 }}
 * @SolARComponentProperty{ drawSceneAxis,
 *                          if not 0\, a gizmo showing the coordinate system axis of the scene reference is displayed,
 *                          @SolARComponentPropertyDescNum{ uint, [0\,1], 1 }}
 * @SolARComponentProperty{ drawWorldAxis,
 *                          if not 0\, a gizmo showing the coordinate system axis of the world reference is displayed,
 *                          @SolARComponentPropertyDescNum{ uint, [0\,1], 1 }}
 * @SolARComponentProperty{ axisScale,
 *                          define the scale of the gizmo displaying the coordinate system center on the scene,
 *                          @SolARComponentPropertyDescNum{ float, [0..MAX FLOAT], 1.f }}
 * @SolARComponentProperty{ pointSize,
 *                          size of points,
 *                          @SolARComponentPropertyDescNum{ float, [0..MAX FLOAT], 2.f }}
 * @SolARComponentProperty{ cameraScale,
 *                          camera scale,
 *                          @SolARComponentPropertyDescNum{ float, [0..MAX FLOAT], 1.f }}
 * @SolARComponentProperty{ zoomSensitivity,
 *                          zoom sensitivity,
 *                          @SolARComponentPropertyDescNum{ float, [0..MAX FLOAT], 10.f }}
 * @SolARComponentProperty{ exitKey,
 *                          the key code to press to close the window. If negative\, no key is defined to close the window,
 *                          @SolARComponentPropertyDescNum{ int, [-1..MAX INT], 27 }}
 *
 * @SolARComponentPropertiesEnd
 *
 */

class SOLAROPENGL_EXPORT_API SolAR3DPointsViewerOpengl : public org::bcom::xpcf::ConfigurableBase,
    public api::display::I3DPointsViewer
{
public:
    SolAR3DPointsViewerOpengl();
    ~SolAR3DPointsViewerOpengl();

    org::bcom::xpcf::XPCFErrorCode onConfigured() override final;
    void unloadComponent () override final;

	/// @brief Display in a windows the 3D point cloud as well as the current camera, and optionnally, the previous frames and keyframes.
	/// @param[in] points, Set of 3D points to display in the 3D viewer.
	/// @param[in] pose, poses of the current camera (transform of the camera defined in world corrdinate system).
	/// @param[in] keyframesPoses (optional), poses of a set of keyframes (transform of the camera defined in world corrdinate system).
	/// @param[in] framePoses (optional), poses of a set of frames (transform of the camera defined in world corrdinate system).
	/// @param[in] points2 (optional), a second set of 3D points to display in the 3D viewer (useful to visualize result of a bundle adjustment).
	/// @param[in] keyframesPoses2 (optional), a second set of keyframes poses (transform of the camera defined in world corrdinate system, useful to visualize result of a bundle adjustment).
	/// @return FrameworkReturnCode::_SUCCESS if the window is created, else FrameworkReturnCode::_ERROR_
    FrameworkReturnCode display(const std::vector<SRef<datastructure::CloudPoint>> & points,
								const datastructure::Transform3Df & pose,
                                const std::vector<datastructure::Transform3Df> & keyframePoses = {},
                                const std::vector<datastructure::Transform3Df> & framePoses = {},
                                const std::vector<SRef<datastructure::CloudPoint>> & points2 = {},
                                const std::vector<datastructure::Transform3Df> & keyframePoses2 = {}) override;

    /// @brief Display in a windows the 3D point cloud as well as the current camera, and optionnally, the previous frames and keyframes.
    /// @param[in] points, Set of 3D points to display in the 3D viewer.
    /// @param[in] pose, poses of the current camera (transform of the camera defined in world corrdinate system).
    /// @param[in] keyframesPoses (optional), poses of a set of keyframes (transform of the camera defined in world corrdinate system).
    /// @param[in] framePoses (optional), poses of a set of frames (transform of the camera defined in world corrdinate system).
    /// @param[in] points2 (optional), a second set of 3D points to display in the 3D viewer (useful to visualize result of a bundle adjustment).
    /// @param[in] keyframesPoses2 (optional), a second set of keyframes poses (transform of the camera defined in world corrdinate system, useful to visualize result of a bundle adjustment).
    /// @return FrameworkReturnCode::_SUCCESS if the window is created, else FrameworkReturnCode::_ERROR_
    FrameworkReturnCode display(const SRef<datastructure::PointCloud> points,
                                const datastructure::Transform3Df & pose,
                                const std::vector<datastructure::Transform3Df> & keyframePoses = {},
                                const std::vector<datastructure::Transform3Df> & framePoses = {},
                                const SRef<datastructure::PointCloud> points2 = nullptr,
                                const std::vector<datastructure::Transform3Df> & keyframePoses2 = {}) override;

protected:
    static SolAR3DPointsViewerOpengl * m_instance;

private:

    /// @brief the title of the window on which the image will be displayed
    std::string m_title = "";

    /// @brief the width of the window on which the image will be displayed (if <=0, the width of the input image)
    unsigned int m_width = 0;

    /// @brief the height of the window on which the image will be displayed (if <=0, the height of the input image)
    unsigned int m_height = 0;

    /// @brief background color
    std::vector<unsigned int> m_backgroundColor = {255,255,255};

    /// @brief if null, the color of each point is used, else the color defined in parameter by user is used
    unsigned int m_fixedPointsColor = 1;

    /// @brief points color
    std::vector<unsigned int> m_pointsColor = {0,255,0};

    /// @brief points color for the second cloud
    std::vector<unsigned int> m_points2Color = {255, 0, 0};

    /// @brief display points color according to class label 
    unsigned int m_usePointsColorFromClassLabel = 0;

    /// @brief colormap file mapping class label to RGB color 
    std::string m_classLabelColorMapPath = "";

    /// @brief colormap mapping class label to RGB triples
    std::vector<datastructure::Vector3f> m_colorMap;

    /// @brief camera color
    std::vector<unsigned int> m_cameraColor = {0,0,255};

    /// @brief if not null, each keyframe pose is drawn as a camera, else as a point
    unsigned int m_keyframeAsCamera;

    /// @brief frame color
    std::vector<unsigned int> m_framesColor = {180,180,180};

    /// @brief keyframe color
    std::vector<unsigned int> m_keyframesColor = {0, 255, 0};

    /// @brief keyframe color for the second vector of keyframe
    std::vector<unsigned int> m_keyframes2Color = {255, 0, 0};

    /// @brief if not null, a gizmo showing the coordinate system of the camera is displayed
    unsigned int m_drawCameraAxis = 1;

    /// @brief if not null, a gizmo showing the coordinate system axis of the scene reference is displayed
    unsigned int m_drawSceneAxis = 1;

    /// @brief if not null, a gizmo showing the coordinate system axis of the world reference is displayed
    unsigned int m_drawWorldAxis = 1;

    /// @brief define the scale of the gizmo displaying the coordinate system center on the scene
    float m_axisScale = 1.0;

    /// @brief size of points
    float m_pointSize = 2.0f;

    /// @brief camera scale
    float m_cameraScale = 1.0f;

    /// @brief zoom sensitivity
    float m_zoomSensitivity = 10.0f;

    /// @brief The key code to press to close the window. If negative, no key is defined to close the window
    int m_exitKey = 27;

    /// @brief The key code to press to increase rotation about X axis. If negative, no key is defined.
    int m_increaseRotationXKey = -1;

    /// @brief The key code to press to decrease rotation about X axis. If negative, no key is defined.
    int m_decreaseRotationXKey = -1;

    /// @brief The key code to press to increase rotation about Y axis. If negative, no key is defined.
    int m_increaseRotationYKey = -1;

    /// @brief The key code to press to decrease rotation about Y axis. If negative, no key is defined.
    int m_decreaseRotationYKey = -1;

    /// @brief The key code to press to increase rotation about Z axis. If negative, no key is defined.
    int m_increaseRotationZKey = -1;

    /// @brief The key code to press to decrease rotation about Z axis. If negative, no key is defined.
    int m_decreaseRotationZKey = -1;

    /// @brief The key code to press to reset all rotation values to 0. If negative, no key is defined.
    int m_resetRotationKey = -1;

    int m_glWindowID = -1;
    std::vector<SRef<datastructure::CloudPoint>> m_points;
    std::vector<SRef<datastructure::CloudPoint>> m_points2;
    datastructure::Transform3Df m_cameraPose;
    std::vector<datastructure::Transform3Df> m_keyframePoses;
    std::vector<datastructure::Transform3Df> m_keyframePoses2;
    std::vector<datastructure::Transform3Df> m_framePoses;
    gl_camera m_glcamera;
    datastructure::Point3Df m_sceneCenter;
    float m_sceneSize;
    unsigned int m_resolutionX;
    unsigned int m_resolutionY;
    bool m_exitKeyPressed = false;
    bool m_firstDisplay = true;
    float m_rotationStep = 0.01;
    float m_rotationX = 0.0, m_rotationY = 0.0, m_rotationZ = 0.0;

    void rotate(const float rx, const float ry, const float rz);

    void OnMainLoop() ;
    void OnRender() ;
    void OnResizeWindow(int _w , int _h) ;
    void OnKeyBoard(unsigned char key, int x, int y) ;
    void OnMouseMotion(int x, int y);
    void OnMouseState(int button, int state, int x, int y);

    static void MainLoop()
    {
        m_instance->OnMainLoop();
    }

    static void Render()
    {
        m_instance->OnRender();
    }
    static void ResizeWindow(int _w , int _h)
    {
        m_instance->OnResizeWindow(_w, _h);
    }
    static void KeyBoard(unsigned char key, int x, int y)
    {
        m_instance->OnKeyBoard(key, x , y);
    }

    static void MouseMotion(int x, int y)
    {
        m_instance->OnMouseMotion(x,  y);
    }
    static void MouseState(int button, int state, int x, int y)
    {
        m_instance->OnMouseState(button, state, x , y);
    }
};

}
}
}

#endif // SOLAR3DPOINTSVIEWEROPENGL_H
