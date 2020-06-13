;; Auto-generated. Do not edit!


(when (boundp 'as1::peace)
  (if (not (find-package "AS1"))
    (make-package "AS1"))
  (shadow 'peace (find-package "AS1")))
(unless (find-package "AS1::PEACE")
  (make-package "AS1::PEACE"))

(in-package "ROS")
;;//! \htmlinclude peace.msg.html


(defclass as1::peace
  :super ros::object
  :slots (_velx _vely _posx _posy ))

(defmethod as1::peace
  (:init
   (&key
    ((:velx __velx) 0.0)
    ((:vely __vely) 0.0)
    ((:posx __posx) 0.0)
    ((:posy __posy) 0.0)
    )
   (send-super :init)
   (setq _velx (float __velx))
   (setq _vely (float __vely))
   (setq _posx (float __posx))
   (setq _posy (float __posy))
   self)
  (:velx
   (&optional __velx)
   (if __velx (setq _velx __velx)) _velx)
  (:vely
   (&optional __vely)
   (if __vely (setq _vely __vely)) _vely)
  (:posx
   (&optional __posx)
   (if __posx (setq _posx __posx)) _posx)
  (:posy
   (&optional __posy)
   (if __posy (setq _posy __posy)) _posy)
  (:serialization-length
   ()
   (+
    ;; float64 _velx
    8
    ;; float64 _vely
    8
    ;; float64 _posx
    8
    ;; float64 _posy
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64 _velx
       (sys::poke _velx (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _vely
       (sys::poke _vely (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _posx
       (sys::poke _posx (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _posy
       (sys::poke _posy (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64 _velx
     (setq _velx (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _vely
     (setq _vely (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _posx
     (setq _posx (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _posy
     (setq _posy (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get as1::peace :md5sum-) "e6be4b315e1490f51ec3a3cda103c9a9")
(setf (get as1::peace :datatype-) "as1/peace")
(setf (get as1::peace :definition-)
      "float64 velx
float64 vely
float64 posx
float64 posy

")



(provide :as1/peace "e6be4b315e1490f51ec3a3cda103c9a9")


