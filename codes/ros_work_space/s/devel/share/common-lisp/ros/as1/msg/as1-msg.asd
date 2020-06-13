
(cl:in-package :asdf)

(defsystem "as1-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "PP" :depends-on ("_package_PP"))
    (:file "_package_PP" :depends-on ("_package"))
    (:file "peace" :depends-on ("_package_peace"))
    (:file "_package_peace" :depends-on ("_package"))
  ))