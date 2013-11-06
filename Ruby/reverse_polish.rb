class RPNCalculator
    def evaluate(expression)
        expression = expression.split
        operands = []
        evaluation = []

        expression.each do |x|
            case x
                when /\d/
                    evaluation.push(x.to_f)
                when "-", "/", "*", "+", "**"
                    operands = evaluation.pop(2)
                    evaluation.push(operands[0].send(x, operands[1]))
            end
        end
        puts evaluation
    end
end


rpn = RPNCalculator.new
rpn.evaluate("20 10 5 4 + * -")
