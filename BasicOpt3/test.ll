; ModuleID = 'test.c'
target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v64:64:64-v128:128:128-a0:0:64-s0:64:64-f80:128:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@.str = private unnamed_addr constant [3 x i8] c"hi\00", align 1
@.str1 = private unnamed_addr constant [6 x i8] c"hello\00", align 1
@.str2 = private unnamed_addr constant [4 x i8] c"BYE\00", align 1
@.str3 = private unnamed_addr constant [4 x i8] c"\0Ahi\00", align 1
@.str4 = private unnamed_addr constant [5 x i8] c"\0Abye\00", align 1

; Function Attrs: nounwind uwtable
define void @foo() #0 {
entry:
  %call = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([3 x i8]* @.str, i32 0, i32 0))
  ret void
}

declare i32 @printf(i8*, ...) #1

; Function Attrs: nounwind uwtable
define i32 @main() #0 {
entry:
  %retval = alloca i32, align 4
  %i = alloca i32, align 4
  %x = alloca i32, align 4
  %y = alloca i32, align 4
  %z = alloca i32, align 4
  %a = alloca i32, align 4
  store i32 0, i32* %retval
  %call = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([6 x i8]* @.str1, i32 0, i32 0))
  %call1 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([4 x i8]* @.str2, i32 0, i32 0))
  store i32 2, i32* %i, align 4
  store i32 0, i32* %x, align 4
  br label %for.cond

for.cond:                                         ; preds = %for.inc13, %entry
  %0 = load i32* %x, align 4
  %cmp = icmp slt i32 %0, 2
  br i1 %cmp, label %for.body, label %for.end15

for.body:                                         ; preds = %for.cond
  store i32 0, i32* %y, align 4
  br label %for.cond2

for.cond2:                                        ; preds = %for.inc, %for.body
  %1 = load i32* %y, align 4
  %cmp3 = icmp slt i32 %1, 3
  br i1 %cmp3, label %for.body4, label %for.end

for.body4:                                        ; preds = %for.cond2
  %call5 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([4 x i8]* @.str3, i32 0, i32 0))
  br label %for.inc

for.inc:                                          ; preds = %for.body4
  %2 = load i32* %y, align 4
  %inc = add nsw i32 %2, 1
  store i32 %inc, i32* %y, align 4
  br label %for.cond2

for.end:                                          ; preds = %for.cond2
  store i32 0, i32* %y, align 4
  br label %for.cond6

for.cond6:                                        ; preds = %for.inc10, %for.end
  %3 = load i32* %y, align 4
  %cmp7 = icmp slt i32 %3, 3
  br i1 %cmp7, label %for.body8, label %for.end12

for.body8:                                        ; preds = %for.cond6
  %call9 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([4 x i8]* @.str3, i32 0, i32 0))
  br label %for.inc10

for.inc10:                                        ; preds = %for.body8
  %4 = load i32* %y, align 4
  %inc11 = add nsw i32 %4, 1
  store i32 %inc11, i32* %y, align 4
  br label %for.cond6

for.end12:                                        ; preds = %for.cond6
  br label %for.inc13

for.inc13:                                        ; preds = %for.end12
  %5 = load i32* %x, align 4
  %inc14 = add nsw i32 %5, 1
  store i32 %inc14, i32* %x, align 4
  br label %for.cond

for.end15:                                        ; preds = %for.cond
  %call16 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([5 x i8]* @.str4, i32 0, i32 0))
  %6 = load i32* %retval
  ret i32 %6
}

attributes #0 = { nounwind uwtable "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = metadata !{metadata !"clang version 3.4.2 (tags/RELEASE_34/dot2-final)"}
