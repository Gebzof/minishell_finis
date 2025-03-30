#!/bin/bash

TEMP_DIR=$(mktemp -d)
echo "📁 Dossier temporaire créé : $TEMP_DIR"

TEST_FILE="test_cases.txt"
BASH_OUT="$TEMP_DIR/bash_output.txt"
MINISHELL_OUT="$TEMP_DIR/minishell_output.txt"
CLEAN_BASH_OUT="$TEMP_DIR/clean_bash_output.txt"
CLEAN_MINISHELL_OUT="$TEMP_DIR/clean_minishell_output.txt"
DIFF_OUT="$TEMP_DIR/diff_output.txt"
MINISHELL_EXEC="./minishell"

# Vérification de l'existence du fichier de test
if [[ ! -f "$TEST_FILE" ]]; then
    echo "Erreur : Le fichier $TEST_FILE est introuvable."
    rm -rf "$TEMP_DIR"
    exit 1
fi

# Fonction pour exécuter et comparer les résultats
run_test() {
    local cmd="$1"
    echo "🔹 Test : $cmd"

    # Exécution dans bash
    (echo "$cmd"; echo "exit") | bash --posix > "$BASH_OUT" 2>&1

    # Exécution dans minishell en forçant la sortie
    (cd "$TEMP_DIR" && (echo "$cmd"; echo "exit") | $MINISHELL_EXEC) > "$MINISHELL_OUT" 2>&1

    sed -i '1d' "$MINISHELL_OUT"
    sed -i '1d' "$MINISHELL_OUT"
    sed -i ''s/exit//g'' "$MINISHELL_OUT"
    echo -e "\n" >> $BASH_OUT
    # Suppression des codes ANSI et du prompt de minishell
    sed -E "s/\x1B\[[0-9;]*[mK]//g" "$BASH_OUT" > "$CLEAN_BASH_OUT"
    sed -E "s/\x1B\[[0-9;]*[mK]//g" "$MINISHELL_OUT" > "$CLEAN_MINISHELL_OUT"
    # Supprimer tout avant le mot 'exit' dans les sorties nettoyées
    sed -i '2d' "$CLEAN_MINISHELL_OUT"
    # Comparaison des sorties
    sed -i '/^$/d' "$CLEAN_BASH_OUT"
    sed -i '/^$/d' "$CLEAN_MINISHELL_OUT"

    if diff -u "$CLEAN_BASH_OUT" "$CLEAN_MINISHELL_OUT" > "$DIFF_OUT"; then
        echo "✅ Identique"
    else
        echo "❌ Différence détectée !"
        cat "$DIFF_OUT"
    fi
    echo "----------------------------------"
}

# Exécuter les tests à partir du fichier
while IFS= read -r line; do
    [[ -z "$line" || "$line" =~ ^# ]] && continue  # Ignorer les lignes vides et commentaires
    run_test "$line"
done < "$TEST_FILE"

# Nettoyage du dossier temporaire
echo "🧹 Nettoyage du dossier temporaire..."
rm -rf "$TEMP_DIR"
echo "✨ Nettoyage terminé"