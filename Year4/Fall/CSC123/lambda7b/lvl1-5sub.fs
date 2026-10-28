// Level 1: Binop (*, /, %, ==, <, &&, ||), Uniop (!), Ifelse
    | Binop ("*", a,b) -> numap2 (fun (x,y) -> x*y) (eval stack a) (eval stack b)

    | Binop ("/", a,b) -> numbind2 (fun (x,y) -> if y=0 then RuntimeError("division by zero") else Num(x/y)) (eval stack a) (eval stack b)

    | Binop ("%", a,b) -> numbind2 (fun (x,y) -> if y=0 then RuntimeError("mod by zero") else Num(x%y)) (eval stack a) (eval stack b)

    | Binop ("==",a,b) ->
        match ((eval stack a), (eval stack b)) with
            | (Num(x),Num(y)) -> if x=y then Num 1 else Num 0
            | _ -> RuntimeError("== requires two numbers")

    | Binop ("<",a,b) ->
        match ((eval stack a), (eval stack b)) with
            | (Num(x),Num(y)) -> if x<y then Num 1 else Num 0
            | (RuntimeError er, _) -> RuntimeError er
            | (_, RuntimeError er) -> RuntimeError er
            | _ -> RuntimeError("< requires two numbers")

    | Binop ("&&",a,b) ->
        match (eval stack a) with
            | RuntimeError er -> RuntimeError er
            | Num 0 -> Num 0
            | Num _ ->
                match (eval stack b) with
                    | RuntimeError er -> RuntimeError er
                    | Num n -> if n=0 then Num 0 else Num 1
                    | _ -> RuntimeError "invalid op for &&"
            | _ -> RuntimeError "invalid op for &&"

    | Binop ("||",a,b) ->
        match (eval stack a) with
            | RuntimeError er -> RuntimeError er
            | Num 0 ->
                match (eval stack b) with
                    | RuntimeError er -> RuntimeError er
                    | Num n -> if n=0 then Num 0 else Num 1
                    | _ -> RuntimeError "invalid op for ||"
            | Num _ -> Num 1
            | _ -> RuntimeError "invalid op for ||"

    | Uniop("!", a) ->
        match (eval stack a) with
            | RuntimeError er -> RuntimeError er
            | Num n -> if n=0 then Num 1 else Num 0
            | _ -> RuntimeError "! requires a number"

    | Ifelse(cond, tcase, fcase) ->
        match (eval stack cond) with
            | RuntimeError er -> RuntimeError er
            | Num n -> if n=0 then eval stack fcase else eval stack tcase
            | _ -> RuntimeError "if condition requires a number"

// Level 2: Assign, While
    | Assign (Var x, valuetox) ->
      match lookup stack x with
      | Some(variableRef) ->
          let evaluatedValue = eval stack valuetox
          match evaluatedValue with
          | RuntimeError message -> RuntimeError message
          | _ ->
              variableRef := evaluatedValue
              evaluatedValue
      | None ->
          RuntimeError(sprintf "%s not found in scope" x)

    | While (condition, body) -> 
      match eval stack condition with 
      | RuntimeError message -> RuntimeError message
      | Num 0 -> Void 
      | Num n -> 
          match eval stack body with
          | RuntimeError message -> RuntimeError message
          | _ -> eval stack (While(condition, body))
      | _ -> RuntimeError "while condition requires a number"

// Level 3: Lambda, Apply
// Level 5: Uses these same Lambda and Apply cases, plus Assign under Level 2.
    | Lambda (parameter, body) -> 
      Closure(stack, Lambda(parameter,body))
    
    | Apply(functionExpr, argumentExpr) ->
        match eval stack functionExpr with
        | RuntimeError message -> RuntimeError message
        | Closure(capturedStack, Lambda(parameter, body)) ->
            match eval stack argumentExpr with
            | RuntimeError message -> RuntimeError message
            | argumentValue ->
                let functionStack =
                    (parameter, ref argumentValue) :: capturedStack
                eval functionStack body
        | _ -> RuntimeError "attempted to call a nonfunction"

// Level 4: Let, Sequence
    | Let(name, valExpression, body) -> 
        match eval stack valExpression with 
        | RuntimeError message -> RuntimeError message
        | value ->
            let localStack = (name, ref value) :: stack 
            eval localStack body 

    | Sequence steps ->
        let preparedSteps =
            List.rev steps
            |> List.collect (function
                | Define(name, Lambda(parameter, body)) ->
                    [ Define(name, Void)
                      Assign(Var name, Lambda(parameter, body))
                      Void ]
                | step -> [step]) //step is one item from list of steps 
        eval_seq stack preparedSteps

