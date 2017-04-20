#pragma once
#include <Urho3D/Input/Controls.h>
#include <Urho3D/Scene/LogicComponent.h>
#include <Urho3D/Physics/PhysicsUtils.h>

namespace Urho3D
{
    class Constraint;
    class Node;
    class RigidBody;
}
using namespace Urho3D;

const int CTRL_FORWARD = (1 << 0);
const int CTRL_BACK = (1 << 1);
const int CTRL_LEFT = (1 << 2);
const int CTRL_RIGHT = (1 << 3);
const int CTRL_BRAKE = (1 << 4);
const float YAW_SENSITIVITY = 0.1f;
const float ENGINE_POWER = 10.0f;
const float MAX_WHEEL_ANGLE = 22.5f;
// Vehicle component, responsible for physical movement according to controls.
// Encapsulates RaycastVehicle
class Vehicle : public LogicComponent
{
        URHO3D_OBJECT(Vehicle, LogicComponent)
    public:
        /// Construct.
        Vehicle(Context* context);
        ~Vehicle();
        /// Register object factory and attributes.
        static void RegisterObject(Context* context);
        /// Perform post-load after deserialization. Acquire the components from the scene nodes.
        virtual void ApplyAttributes();

/// Initialize the vehicle. Create rendering and physics components. Called by the application.
        void Init();

/// Handle physics world update. Called by LogicComponent base class.
        virtual void FixedUpdate(float timeStep);
/// Updating wheel effects here
        virtual void PostUpdate(float timeStep);

/// Movement controls.
        Controls controls_;
/// Steering control
        float GetSteering()
        {
            return steering_;
        }
        void SetSteering(float steering)
        {
            steering_ = steering;
        }
        float GetWheelRadius()
        {
            return wheelRadius_;
        }
        float GetWheelWidth()
        {
            return wheelWidth_;
        }
        VariantVector GetParticleNodeIDsAttr() const;
        void SetParticleNodeIDsAttr(const VariantVector& value);
    private:
        void CreateEmitter(Vector3 place);
        /// Current left/right steering amount (-1 to 1.)
        float steering_;
        float vehicleSteering_;
        float engineForce_;
        float brakingForce_;
        float maxEngineForce_;
        float wheelRadius_;
        float suspensionRestLength_;
        float wheelWidth_;
        float suspensionStiffness_;
        float suspensionDamping_;
        float suspensionCompression_;
        float wheelFriction_;
        float rollInfluence_;
        Vector<Node*> particleEmitterNodeList_;
        Vector3 prevVelocity_;
        VariantVector emitterSaveData_;
        Vector3 connectionPoints_[4];
};
