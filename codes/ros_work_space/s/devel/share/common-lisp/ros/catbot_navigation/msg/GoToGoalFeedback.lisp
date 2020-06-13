; Auto-generated. Do not edit!


(cl:in-package catbot_navigation-msg)


;//! \htmlinclude GoToGoalFeedback.msg.html

(cl:defclass <GoToGoalFeedback> (roslisp-msg-protocol:ros-message)
  ((err_x
    :reader err_x
    :initarg :err_x
    :type cl:float
    :initform 0.0)
   (err_y
    :reader err_y
    :initarg :err_y
    :type cl:float
    :initform 0.0)
   (e_psi
    :reader e_psi
    :initarg :e_psi
    :type cl:float
    :initform 0.0))
)

(cl:defclass GoToGoalFeedback (<GoToGoalFeedback>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <GoToGoalFeedback>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'GoToGoalFeedback)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name catbot_navigation-msg:<GoToGoalFeedback> is deprecated: use catbot_navigation-msg:GoToGoalFeedback instead.")))

(cl:ensure-generic-function 'err_x-val :lambda-list '(m))
(cl:defmethod err_x-val ((m <GoToGoalFeedback>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader catbot_navigation-msg:err_x-val is deprecated.  Use catbot_navigation-msg:err_x instead.")
  (err_x m))

(cl:ensure-generic-function 'err_y-val :lambda-list '(m))
(cl:defmethod err_y-val ((m <GoToGoalFeedback>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader catbot_navigation-msg:err_y-val is deprecated.  Use catbot_navigation-msg:err_y instead.")
  (err_y m))

(cl:ensure-generic-function 'e_psi-val :lambda-list '(m))
(cl:defmethod e_psi-val ((m <GoToGoalFeedback>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader catbot_navigation-msg:e_psi-val is deprecated.  Use catbot_navigation-msg:e_psi instead.")
  (e_psi m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <GoToGoalFeedback>) ostream)
  "Serializes a message object of type '<GoToGoalFeedback>"
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'err_x))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'err_y))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'e_psi))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <GoToGoalFeedback>) istream)
  "Deserializes a message object of type '<GoToGoalFeedback>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'err_x) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'err_y) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'e_psi) (roslisp-utils:decode-double-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<GoToGoalFeedback>)))
  "Returns string type for a message object of type '<GoToGoalFeedback>"
  "catbot_navigation/GoToGoalFeedback")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GoToGoalFeedback)))
  "Returns string type for a message object of type 'GoToGoalFeedback"
  "catbot_navigation/GoToGoalFeedback")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<GoToGoalFeedback>)))
  "Returns md5sum for a message object of type '<GoToGoalFeedback>"
  "60a20c6270af6bc8e54a51252ccf7a37")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'GoToGoalFeedback)))
  "Returns md5sum for a message object of type 'GoToGoalFeedback"
  "60a20c6270af6bc8e54a51252ccf7a37")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<GoToGoalFeedback>)))
  "Returns full string definition for message of type '<GoToGoalFeedback>"
  (cl:format cl:nil "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======~%float64 err_x~%float64 err_y~%float64 e_psi~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'GoToGoalFeedback)))
  "Returns full string definition for message of type 'GoToGoalFeedback"
  (cl:format cl:nil "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======~%float64 err_x~%float64 err_y~%float64 e_psi~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <GoToGoalFeedback>))
  (cl:+ 0
     8
     8
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <GoToGoalFeedback>))
  "Converts a ROS message object to a list"
  (cl:list 'GoToGoalFeedback
    (cl:cons ':err_x (err_x msg))
    (cl:cons ':err_y (err_y msg))
    (cl:cons ':e_psi (e_psi msg))
))
