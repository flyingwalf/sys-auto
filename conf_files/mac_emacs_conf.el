(require 'linum)
(add-hook 'find-file-hooks (lambda () (linum-mode 1)))
(setq make-backup-files nil)
(setq-default c-default-style "linux"
	      c-basic-offset 4
	      tab-width 4)

;; key bindings
(when (eq system-type 'darwin) ;; mac specific settings
  (setq mac-option-modifier 'alt)
  (setq mac-command-modifier 'meta)
  (global-set-key [kp-delete] 'delete-char) ;; sets fn-delete to be right-delete
)

(add-to-list 'load-path "~/.emacs.d/site-lisp/")
;;(require 'eide)
;;(eide-start)
(setq x-alt-keysym 'meta)

;;Don't auto backupfiles
(setq make-backup-files nil)

;;Using ibuffer
(global-set-key (kbd "C-x C-b") 'ibuffer)

;;Set parentheses matching mode
(setq show-paren-delay 0)
(show-paren-mode 1)

;;Split the window vertically by default
(setq split-height-threshold nil)
(setq split-width-threshold 0)


;;(custom-set-faces
  ;; custom-set-faces was added by Custom.
  ;; If you edit it by hand, you could mess it up, so be careful.
  ;; Your init file should contain only one such instance.
  ;; If there is more than one, they won't work right.
 ;;'(default ((t (:inherit nil :stipple nil :background "white" :foreground "black" :inverse-video nil :box nil :strike-through nil :overline nil :underline nil :slant normal :weight normal :height 181 :width semi-condensed :foundry "b&h" :family "Lucida Console")))))

(custom-set-faces
  ;; custom-set-faces was added by Custom.
  ;; If you edit it by hand, you could mess it up, so be careful.
  ;; Your init file should contain only one such instance.
  ;; If there is more than one, they won't work right.
 '(default ((t (:inherit nil :stipple nil :inverse-video nil :box nil :strike-through nil :overline nil :underline nil :slant normal :weight normal :height 181 :width semi-condensed :foundry "b&h" :family "Lucida Console")))))
