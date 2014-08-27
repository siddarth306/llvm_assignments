; ModuleID = '<stdin>'
target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v64:64:64-v128:128:128-a0:0:64-s0:64:64-f80:128:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: nounwind uwtable
define i32 @main() #0 {
entry:
  %a = alloca i32, align 4
  %b = alloca i32, align 4
  store i32 1, i32* %a, align 4
  store i32 4, i32* %b, align 4
  %0 = load i32* %b, align 4
  %1 = load i32* %b, align 4
  %val0MinusOne = sub i32 %0, 1
  %val1MinusOne = sub i32 %1, 1
  %isval0PowerOfTwo = and i32 %0, %val0MinusOne
  %isval1PowerOfTwo = and i32 %1, %val1MinusOne
  %2 = icmp eq i32 %isval0PowerOfTwo, 0
  br label %ifstart

ifstart:                                          ; preds = %entry
  %mul = mul i32 %0, %1
  store i32 %mul, i32* %b, align 4
  ret i32 0
}

attributes #0 = { nounwind uwtable "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = metadata !{metadata !"clang version 3.4.2 (tags/RELEASE_34/dot2-final)"}
