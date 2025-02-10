#!/bin/bash

# Nettoyage des fichiers de test précédents
rm -f test1.txt test2.txt test3.txt test_output.txt error_output.txt

echo "Démarrage des tests..."

# Test 1 : Redirection de sortie ">"
echo "test 1" > test1.txt
.././my_sh -c "cat test1.txt > test2.txt"

if [ "$(cat test1.txt)" = "$(cat test2.txt)" ]; then
    echo "✅ Test 1: Redirection '>' OK"
else
    echo "❌ Test 1: Redirection '>' KO"
fi

# Test 2 : Commande pwd
.././my_sh -c "pwd > test1.txt"

if [ "$(pwd)" = "$(cat test1.txt)" ]; then
    echo "✅ Test 2: pwd OK"
else
    echo "❌ Test 2: pwd KO"
fi

# Test 3 : Built-in cd
.././my_sh -c "cd .. && pwd > test2.txt"

if [ "$(cd .. && pwd)" = "$(cat ../test2.txt)" ]; then
    echo "✅ Test 3: cd OK"
else
    echo "Value of $(cd .. && pwd)" | od -c
    echo "Value of $(cat ../test2.txt)" | od -c

    echo "❌ Test 3: cd KO"
fi

cd TEST

# Test 4 : Redirection d'entrée "<"
echo "Hello" > test1.txt
.././my_sh -c "cat < test1.txt" > test2.txt

if [ "$(cat test1.txt)" = "$(cat test2.txt)" ]; then
    echo "✅ Test 4: Redirection '<' OK"
else
    echo "❌ Test 4: Redirection '<' KO"
fi

# Test 5 : Redirection d'append ">>"
echo "Append test" > test1.txt
.././my_sh -c "echo 'Appended text' >> test1.txt"

if grep -q "Appended text" test1.txt; then
    echo "✅ Test 5: Redirection '>>' OK"
else
    echo "❌ Test 5: Redirection '>>' KO"
fi

# Test 6 : Exécution d'une commande simple
.././my_sh -c "echo 'Hello World'" > test1.txt

if grep -q "Hello World" test1.txt; then
    echo "✅ Test 6: Commande simple OK"
else
    echo "❌ Test 6: Commande simple KO"
fi

# Test 7 : Commande inexistante
.././my_sh -c "Commande introuvable" > error_output.txt

if grep -q "Commande introuvable" error_output.txt; then
    echo "✅ Test 7: Gestion des erreurs OK"
else
    echo "❌ Test 7: Gestion des erreurs KO"
fi

# Test 8 : Pipe simple
.././my_sh -c "echo 'Hello' | grep H" > test_output.txt

if grep -q "Hello" test_output.txt; then
    echo "✅ Test 8: Pipe simple OK"
else
    echo "❌ Test 8: Pipe simple KO"
fi

# Test 9 : Pipe avec plusieurs commandes
.././my_sh -c "echo 'Hello World' | tr ' ' '\n' | wc -l" > test_output.txt

if grep -q "2" test_output.txt; then
    echo "✅ Test 9: Pipe multiple OK"
else
    echo "❌ Test 9: Pipe multiple KO"
fi

# Test 10 : Exécution en arrière-plan "&"
.././my_sh -c "sleep 2 & echo 'Done'" > test_output.txt

if grep -q "Done" test_output.txt; then
    echo "✅ Test 10: Background OK"
else
    echo "❌ Test 10: Background KO"
fi

# Test 11 : Liste de commandes avec ";"
.././my_sh -c "echo 'First'; echo 'Second'" > test_output.txt

if grep -q "First" test_output.txt && grep -q "Second" test_output.txt; then
    echo "✅ Test 11: Séparateur ';' OK"
else
    echo "❌ Test 11: Séparateur ';' KO"
fi

# Test 12 : Commande exit
echo "exit" | .././my_sh > test_output.txt

if [ $? -eq 0 ]; then
    echo "✅ Test 12: exit OK"
else
    echo "❌ Test 12: exit KO"
fi

# Test 13 : Variable d'environnement
export TEST_VAR="Hello"
.././my_sh -c "echo \$TEST_VAR" > test_output.txt

if grep -q "Hello" test_output.txt; then
    echo "✅ Test 13: Variable d'environnement OK"
else
    echo "❌ Test 13: Variable d'environnement KO"
fi

# Test 14 : Historique des commandes
echo "ls" | .././my_sh > test_output.txt
.././my_sh -c "history" > test_output.txt

if grep -q "ls" test_output.txt; then
    echo "✅ Test 14: Historique OK"
else
    echo "❌ Test 14: Historique KO"
fi

# Test 15 : Exécution d'un script batch
echo "echo 'Batch Test'" > batch_script.sh
.././my_sh < batch_script.sh > test_output.txt

if grep -q "Batch Test" test_output.txt; then
    echo "✅ Test 15: Mode batch OK"
else
    echo "❌ Test 15: Mode batch KO"
fi

# Test 16 : Commande avec arguments
.././my_sh -c "echo arg1 arg2 arg3" > test_output.txt

if grep -q "arg1 arg2 arg3" test_output.txt; then
    echo "✅ Test 16: Commande avec arguments OK"
else
    echo "❌ Test 16: Commande avec arguments KO"
fi

# Test 17 : Test des alias (si supporté)
.././my_sh -c "alias ll='ls -l'" > /dev/null
.././my_sh -c "ll" > test_output.txt

if grep -q "total" test_output.txt; then
    echo "✅ Test 17: Alias OK"
else
    echo "❌ Test 17: Alias KO"
fi

# Test 18 : Test des jokers "*"
touch file1.txt file2.txt
.././my_sh -c "ls file*.txt" > test_output.txt

if grep -q "file1.txt" test_output.txt && grep -q "file2.txt" test_output.txt; then
    echo "✅ Test 18: Jokers OK"
else
    echo "❌ Test 18: Jokers KO"
fi

# Test 19 : Suppression de fichier
echo "to delete" > test1.txt
.././my_sh -c "rm test1.txt"

if [ ! -f test1.txt ]; then
    echo "✅ Test 19: Suppression OK"
else
    echo "❌ Test 19: Suppression KO"
fi

# Test 20 : Test du Here Document "<<"
.././my_sh -c "cat << EOF > test1.txt
Hello HereDoc
EOF" 

if grep -q "Hello HereDoc" test1.txt; then
    echo "✅ Test 20: Here Document OK"
else
    echo "❌ Test 20: Here Document KO"
fi

echo "Tests terminés ✅"