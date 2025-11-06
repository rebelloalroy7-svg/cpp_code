import 'package:flutter/material.dart';
import 'package:math_expressions/math_expressions.dart';
import '../db/db_helper.dart';

class CalculatorScreen extends StatefulWidget {
  const CalculatorScreen({super.key});

  @override
  State<CalculatorScreen> createState() => _CalculatorScreenState();
}

class _CalculatorScreenState extends State<CalculatorScreen> {
  String _expression = '';
  String _result = '';

  final List<String> buttons = [
    '7', '8', '9', '÷',
    '4', '5', '6', '×',
    '1', '2', '3', '-',
    '⌫', 'C', '=', '+',
    '0', '.', '%',
  ];

  void _onButtonClick(String value) {
    setState(() {
      if (value == 'C') {
        _expression = '';
        _result = '';
      } else if (value == '⌫') {
        if (_expression.isNotEmpty) {
          _expression = _expression.substring(0, _expression.length - 1);
        }
      } else if (value == '=') {
        try {
          final exp = _expression
              .replaceAll('×', '*')
              .replaceAll('÷', '/')
              .replaceAll('%', '/100');

          Parser p = Parser();
          Expression expression = p.parse(exp);
          ContextModel cm = ContextModel();
          double eval = expression.evaluate(EvaluationType.REAL, cm);
          _result = eval.toString();

          DBHelper.instance.saveCalculation(_expression, _result);
        } catch (e) {
          _result = 'Error';
        }
      } else {
        _expression += value;
      }
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      backgroundColor: Colors.black,
      body: SafeArea(
        child: LayoutBuilder(
          builder: (context, constraints) {
            double screenWidth = constraints.maxWidth;
            double buttonFont = screenWidth < 600 ? 28 : 40;
            double displayFont = screenWidth < 600 ? 36 : 56;
            double resultFont = screenWidth < 600 ? 48 : 72;
            double padding = screenWidth < 600 ? 16 : 32;

            return Column(
              children: [
                Padding(
                  padding: EdgeInsets.all(padding / 2),
                  child: Text(
                    'Smart Calculator',
                    style: TextStyle(
                      color: Colors.deepPurpleAccent,
                      fontSize: displayFont / 1.5,
                      fontWeight: FontWeight.bold,
                    ),
                  ),
                ),
                Expanded(
                  flex: 2,
                  child: Container(
                    width: double.infinity,
                    color: Colors.black87,
                    padding: EdgeInsets.all(padding),
                    child: Column(
                      mainAxisAlignment: MainAxisAlignment.end,
                      crossAxisAlignment: CrossAxisAlignment.end,
                      children: [
                        SingleChildScrollView(
                          scrollDirection: Axis.horizontal,
                          reverse: true,
                          child: Text(
                            _expression,
                            style: TextStyle(
                              fontSize: displayFont,
                              color: Colors.white70,
                            ),
                          ),
                        ),
                        const SizedBox(height: 8),
                        Text(
                          _result,
                          style: TextStyle(
                            fontSize: resultFont,
                            color: Colors.deepPurpleAccent,
                            fontWeight: FontWeight.bold,
                          ),
                        ),
                      ],
                    ),
                  ),
                ),
                Expanded(
                  flex: 3,
                  child: GridView.builder(
                    padding: EdgeInsets.all(padding / 2),
                    itemCount: buttons.length,
                    gridDelegate: SliverGridDelegateWithFixedCrossAxisCount(
                      crossAxisCount: 4,
                      childAspectRatio: screenWidth < 600 ? 1 : 1.3,
                      crossAxisSpacing: 10,
                      mainAxisSpacing: 10,
                    ),
                    itemBuilder: (context, index) {
                      final btn = buttons[index];
                      Color bgColor;

                      if (btn == '=') {
                        bgColor = Colors.deepPurpleAccent;
                      } else if (btn == 'C') {
                        bgColor = Colors.redAccent;
                      } else if (btn == '⌫') {
                        bgColor = Colors.blueAccent;
                      } else if (['÷', '×', '-', '+', '%'].contains(btn)) {
                        bgColor = Colors.orangeAccent;
                      } else {
                        bgColor = Colors.grey[850]!;
                      }

                      return InkWell(
                        borderRadius: BorderRadius.circular(20),
                        splashColor: Colors.deepPurple.withOpacity(0.3),
                        onTap: () => _onButtonClick(btn),
                        child: Container(
                          decoration: BoxDecoration(
                            color: bgColor,
                            borderRadius: BorderRadius.circular(20),
                          ),
                          child: Center(
                            child: Text(
                              btn,
                              style: TextStyle(
                                fontSize: buttonFont,
                                color: Colors.white,
                                fontWeight: FontWeight.bold,
                              ),
                            ),
                          ),
                        ),
                      );
                    },
                  ),
                ),
              ],
            );
          },
        ),
      ),
    );
  }
}
