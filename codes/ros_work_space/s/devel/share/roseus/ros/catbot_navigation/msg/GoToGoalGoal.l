;; Auto-generated. Do not edit!


(when (boundp 'catbot_navigation::GoToGoalGoal)
  (if (not (find-package "CATBOT_NAVIGATION"))
    (make-package "CATBOT_NAVIGATION"))
  (shadow 'GoToGoalGoal (find-package "CATBOT_NAVIGATION")))
(unless (find-package "CATBOT_NAVIGATION::GOTOGOALGOAL")
  (make-package "CATBOT_NAVIGATION::GOTOGOALGOAL"))

(in-package "ROS")
;;//! \htmlinclude GoToGoalGoal.msg.html


(defclass catbot_navigation::GoToGoalGoal
  :super ros::object
  :slots (_x_pos _y_pos _theta ))

(defmethod catbot_navigation::GoToGoalGoal
  (:init
   (&key
    ((:x_pos __x_pos) 0.0)
    ((:y_pos __y_pos) 0.0)
    ((:theta __theta) 0.0)
    )
   (send-super :init)
   (setq _x_pos (float __x_pos))
   (setq _y_pos (float __y_pos))
   (setq _theta (float __theta))
   self)
  (:x_pos
   (&optional __x_pos)
   (if __x_pos (setq _x_pos __x_pos)) _x_pos)
  (:y_pos
   (&optional __y_pos)
   (if __y_pos (setq _y_pos __y_pos)) _y_pos)
  (:theta
   (&optional __theta)
   (if __theta (setq _theta __theta)) _theta)
  (:serialization-length
   ()
   (+
    ;; float64 _x_pos
    8
    ;; float64 _y_pos
    8
    ;; float64 _theta
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64 _x_pos
       (sys::poke _x_pos (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _y_pos
       (sys::poke _y_pos (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _theta
       (sys::poke _theta (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64 _x_pos
     (setq _x_pos (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _y_pos
     (setq _y_pos (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _theta
     (setq _theta (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get catbot_navigation::GoToGoalGoal :md5sum-) "5af55a02225d2e56be88e5e3a36b4ce9")
(setf (get catbot_navigation::GoToGoalGoal :datatype-) "catbot_navigation/GoToGoalGoal")
(setf (get catbot_navigation::GoToGoalGoal :definition-)
      "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======
#Definition of Goal Message

float64 x_pos
float64 y_pos
float64 theta

")



(provide :catbot_navigation/GoToGoalGoal "5af55a02225d2e56be88e5e3a36b4ce9")

