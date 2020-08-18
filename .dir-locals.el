;;; Directory Local Variables
;;; For more information see (info "(emacs) Directory Variables")

((nil
  (projectile-project-compilation-dir . "cmake-build-debug")
  (projectile-project-configure-cmd . "cmake \
-DCMAKE_CXX_COMPILER=clang++ \
-DCMAKE_BUILD_TYPE=DEBUG \
-DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
../")
  (eval . (progn
            (setq-local ccls-initialization-options
                        `(:compilationDatabaseDirectory ,projectile-project-compilation-dir
                          :cache (:directory ,(concat projectile-project-compilation-dir "/.ccls-cache"))))
            (add-hook 'c++-mode-hook 'lsp)))))
