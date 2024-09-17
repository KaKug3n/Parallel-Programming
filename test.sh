#!/bin/bash

# Vérifier si un programme est fourni en paramètre
if [ -z "$1" ]; then
    echo "Usage: $0 <nom_programme>"
    exit 1
fi

# Nom du fichier source du programme sans l'extension .c
program=$1
program_no_ext="${program%.c}"

# Étape 1 : Compiler le programme avec les options de profilage
echo "Compilation de $program avec les options de profilage..."
gcc -fopenmp -pg -o "$program_no_ext" "$program"

# Vérifier si la compilation a réussi
if [ $? -ne 0 ]; then
    echo "Erreur de compilation."
    exit 1
fi

# Étape 2 : Exécuter le programme pour générer le fichier gmon.out
echo "Exécution de $program_no_ext..."
./"$program_no_ext"

# Vérifier si l'exécution a réussi
if [ $? -ne 0 ]; then
    echo "Erreur lors de l'exécution du programme."
    exit 1
fi

# Étape 3 : Lancer gprof pour analyser le fichier gmon.out
echo "Lancement de gprof..."
gprof "$program_no_ext" gmon.out > ${program_no_ext}_gprof_output.txt

time ./"$program_no_ext" > ${program_no_ext}_time_output.txt

# Afficher le fichier de sortie généré par gprof
echo "Analyse terminée. Résultats enregistrés dans ${program_no_ext}_gprof_output.txt."
cat "${program_no_ext}_gprof_output.txt
