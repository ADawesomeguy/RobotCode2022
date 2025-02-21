#include <units/time.h>

#include "rmb/drive/HolonomicTrajectoryCommand.h"

namespace rmb {
    HolonomicTrajectoryCommand::HolonomicTrajectoryCommand(frc::Trajectory t,
                                                           HolonomicDrive& d,
                                                           frc::HolonomicDriveController dc) :
                                                           trajectory(t), drive(d),
                                                           driveController(dc) {}
    
    void HolonomicTrajectoryCommand::Initialize() {
        timer.Reset();
        timer.Start();
    }

    void HolonomicTrajectoryCommand::Execute() {
        units::time::second_t currentTime = units::second_t(timer.Get());
        frc::Trajectory::State desiredState = trajectory.Sample(currentTime);
        auto targetChassisSpeeds = driveController.Calculate(drive.getPose(), desiredState, trajectory.States().back().pose.Rotation());
        drive.driveChassisSpeeds(targetChassisSpeeds);
    }

    void HolonomicTrajectoryCommand::End(bool interrupted) {
        timer.Stop();
    }

    bool HolonomicTrajectoryCommand::IsFinished() {
        return timer.HasElapsed(trajectory.TotalTime());
    }
}