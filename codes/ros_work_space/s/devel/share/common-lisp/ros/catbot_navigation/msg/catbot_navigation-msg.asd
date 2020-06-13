
(cl:in-package :asdf)

(defsystem "catbot_navigation-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :actionlib_msgs-msg
               :std_msgs-msg
)
  :components ((:file "_package")
    (:file "GoToGoalAction" :depends-on ("_package_GoToGoalAction"))
    (:file "_package_GoToGoalAction" :depends-on ("_package"))
    (:file "GoToGoalActionFeedback" :depends-on ("_package_GoToGoalActionFeedback"))
    (:file "_package_GoToGoalActionFeedback" :depends-on ("_package"))
    (:file "GoToGoalActionGoal" :depends-on ("_package_GoToGoalActionGoal"))
    (:file "_package_GoToGoalActionGoal" :depends-on ("_package"))
    (:file "GoToGoalActionResult" :depends-on ("_package_GoToGoalActionResult"))
    (:file "_package_GoToGoalActionResult" :depends-on ("_package"))
    (:file "GoToGoalFeedback" :depends-on ("_package_GoToGoalFeedback"))
    (:file "_package_GoToGoalFeedback" :depends-on ("_package"))
    (:file "GoToGoalGoal" :depends-on ("_package_GoToGoalGoal"))
    (:file "_package_GoToGoalGoal" :depends-on ("_package"))
    (:file "GoToGoalResult" :depends-on ("_package_GoToGoalResult"))
    (:file "_package_GoToGoalResult" :depends-on ("_package"))
  ))