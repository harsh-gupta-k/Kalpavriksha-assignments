#include <stdio.h>
#include "Players_data.h"
#include <string.h>
#include <stdlib.h>
#include <strings.h>
#include<ctype.h>

struct Players
{
    int id;
    char name[50];
    char teamName[20];
    char role[20];
    int totalRuns;
    float battingAverage;
    float strikeRate;
    int wickets;
    float economyRate;
    double performanceIndex;
    struct Players *next;
};

struct Team
{
    int id;
    char name[20];
    int totalPlayers;
    float averageBattingStrikeRate;
};

double calculate_performance_index(struct Players *player)
{
    if (strcasecmp(player->role, "Batsman") == 0)
    {
        return (player->battingAverage * player->strikeRate) / 100;
    }
    else if (strcasecmp(player->role, "Bowler") == 0)
    {
        return (player->wickets * 2) + (100 - player->economyRate);
    }
    else
    {
        return ((player->battingAverage * player->strikeRate) / 100) + (player->wickets * 2);
    }
}

void addPlayer(struct Players **head, Player player)
{
    struct Players *newNode = (struct Players *)malloc(sizeof(struct Players));
    newNode->id = player.id;
    strcpy(newNode->name, player.name);
    strcpy(newNode->teamName, player.team);
    strcpy(newNode->role, player.role);
    newNode->totalRuns = player.totalRuns;
    newNode->battingAverage = player.battingAverage;
    newNode->strikeRate = player.strikeRate;
    newNode->wickets = player.wickets;
    newNode->economyRate = player.economyRate;
    newNode->performanceIndex = calculate_performance_index(newNode);
    newNode->next = NULL;

    if (*head == NULL)
    {
        *head = newNode;
    }
    else
    {
        struct Players *tempNode = *head;
        while (tempNode->next != NULL)
        {
            tempNode = tempNode->next;
        }
        tempNode->next = newNode;
    }
}

void displayPlayersOfTeam(struct Players *head, char *teamName)
{
    struct Players *tempNode = head;
    int totalPlayers = 0;
    float totalStrikeRate = 0;
    int countForAvg = 0;
    printf("Players of team %s\n", teamName);
    printf("Id  Name                     Role        TotalRuns BattingAverage StrikeRate Wickets EconomyRate PerformanceIndex\n");
    while (tempNode != NULL)
    {
        if (strcasecmp(tempNode->teamName, teamName) == 0)
        {
            printf("%-2d %-20s %-15s %-9d %-14.2f %-10.2f %-7d %-11.2f %.2f\n", tempNode->id, tempNode->name, tempNode->role, tempNode->totalRuns, tempNode->battingAverage, tempNode->strikeRate, tempNode->wickets, tempNode->economyRate, tempNode->performanceIndex);
            totalPlayers++;

            if (strcasecmp(tempNode->role, "Batsman") == 0 || strcasecmp(tempNode->role, "All-rounder") == 0)
            {
                totalStrikeRate += tempNode->strikeRate;
                countForAvg++;
            }
        }
        tempNode = tempNode->next;
    }

    if (totalPlayers == 0)
    {
        printf("No players found with team %s", teamName);
        return;
    }

    float avgStrikeRate = (countForAvg > 0) ? totalStrikeRate / countForAvg : 0;

    printf("Total Players: %d\n", totalPlayers);
    printf("Average Batting Strike Rate: %.2f\n", avgStrikeRate);
}

void displayTeamByStrikeRate(struct Players *head)
{
    struct Team teamStats[teamCount];

    for (int player = 0; player < teamCount; player++)
    {
        teamStats[player].id = player + 1;
        strcpy(teamStats[player].name, teams[player]);
        teamStats[player].totalPlayers = 0;
        teamStats[player].averageBattingStrikeRate = 0.0;
    }
    struct Players *tempNode = head;

    float totalSR[10] = {0};
    int countSR[10] = {0};

    while (tempNode != NULL)
    {
        for (int player = 0; player < teamCount; player++)
        {
            if (strcasecmp(tempNode->teamName, teams[player]) == 0)
            {
                teamStats[player].totalPlayers++;

                if (strcasecmp(tempNode->role, "Batsman") == 0 || strcasecmp(tempNode->role, "All-rounder") == 0)
                {
                    totalSR[player] += tempNode->strikeRate;
                    countSR[player]++;
                }
                break;
            }
        }
        tempNode = tempNode->next;
    }

    for (int player = 0; player < teamCount; player++)
    {
        if (countSR[player] > 0)
        {
            teamStats[player].averageBattingStrikeRate = totalSR[player] / countSR[player];
        }
        else
        {
            teamStats[player].averageBattingStrikeRate = 0.0;
        }
    }

    for (int player = 0; player < teamCount - 1; player++)
    {
        for (int j = player + 1; j < teamCount; j++)
        {
            if (teamStats[player].averageBattingStrikeRate < teamStats[j].averageBattingStrikeRate)
            {
                struct Team tempT = teamStats[player];
                teamStats[player] = teamStats[j];
                teamStats[j] = tempT;
            }
        }
    }

    printf("\n---------------------------\n");
    printf("Teams Sorted by Average Batting Strike Rate\n");
    printf("-----------------------------\n");
    printf("ID   Team Name         Avg Bat SR   Total Players\n");
    printf("-----------------------------\n");
    for (int player = 0; player < teamCount; player++)
    {
        printf("%-4d %-18s %-12.2f %-5d\n",
               teamStats[player].id, teamStats[player].name,
               teamStats[player].averageBattingStrikeRate, teamStats[player].totalPlayers);
    }
    printf("----------------------------\n");
}

void displayTopKPlayers(struct Players *head, const char *teamName, const char *role, int K)
{
    struct Players *tempNode = head;

    int count = 0;

    while (tempNode != NULL)
    {
        if (strcasecmp(tempNode->teamName, teamName) == 0 &&
            strcasecmp(tempNode->role, role) == 0)
        {
            count++;
        }
        tempNode = tempNode->next;
    }

    if (count == 0)
    {
        printf("\nNo players found for role %s in team %s.\n", role, teamName);
        return;
    }

    struct Players *arr[count];
    tempNode = head;
    int idx = 0;

    while (tempNode != NULL)
    {
        if (strcasecmp(tempNode->teamName, teamName) == 0 &&
            strcasecmp(tempNode->role, role) == 0)
        {
            arr[idx++] = tempNode;
        }
        tempNode = tempNode->next;
    }

    for (int i = 0; i < count - 1; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            if (arr[i]->performanceIndex < arr[j]->performanceIndex)
            {
                struct Players *swapNode = arr[i];
                arr[i] = arr[j];
                arr[j] = swapNode;
            }
        }
    }

   
    if (K > count)
        K = count;

    printf("\n---------------------------\n");
    printf("Top %d %s of Team %s (Based on Performance Index)\n", K, role, teamName);
    printf("-----------------------------\n");
    printf("ID   Name                     Role         Perf.Index   Runs  SR    Wkts  Eco\n");
    printf("-----------------------------\n");

    for (int player = 0; player < K; player++)
    {
        printf("%-4d %-25s %-12s %-12.2f %-6d %-6.1f %-5d %-5.1f\n",
               arr[player]->id, arr[player]->name, arr[player]->role,
               arr[player]->performanceIndex,
               arr[player]->totalRuns, arr[player]->strikeRate,
               arr[player]->wickets, arr[player]->economyRate);
    }

    printf("----------------------------\n");
}

void displayOverallTopK(struct Players *head, int K)
{
   
    int count = 0;
    struct Players *tempNode = head;

    while (tempNode != NULL)
    {
        count++;
        tempNode = tempNode->next;
    }

    if (count == 0)
    {
        printf("\nNo players available.\n");
        return;
    }

    
    struct Players *arr[count];
    tempNode = head;
    int idx = 0;

    while (tempNode != NULL)
    {
        arr[idx++] = tempNode;
        tempNode = tempNode->next;
    }

    
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            if (arr[i]->performanceIndex < arr[j]->performanceIndex)
            {
                struct Players *swapNode = arr[i];
                arr[i] = arr[j];
                arr[j] = swapNode;
            }
        }
    }

    
    if (K > count)
        K = count;

    
    printf("\n----------------------------\n");
    printf("Overall Top %d Players (All Teams) Based on Performance Index\n", K);
    printf("------------------------------\n");
    printf("ID    Name                     Team            Role        Perf.Index\n");
    printf("------------------------------\n");

    for (int player = 0; player < K; player++)
    {
        printf("%-5d %-24s %-14s %-11s %-10.2f\n",
               arr[player]->id,
               arr[player]->name,
               arr[player]->teamName,
               arr[player]->role,
               arr[player]->performanceIndex);
    }

    printf("-----------------------------\n");
}


// Validation functions

void validString(char *prompt, char *input)
{
    int valid = 0;

    while (!valid)
    {
        printf("%s", prompt);
        scanf(" %[^\n]", input);   

        int hasLetter = 0;
        int hasDigit = 0;

        for (int character = 0; input[character] != '\0'; character++)
        {
            if (isalpha(input[character]))
                hasLetter = 1;

            if (isdigit(input[character]))
                hasDigit = 1;
        }

        if (hasDigit)
        {
            printf(" Invalid String.\n");
        }
        else if (!hasLetter)
        {
            printf(" Invalid String\n");
        }
        else
        {
            valid = 1;
        }
    }
}



int main()
{
    struct Players *head = NULL;

    // Load all players into linked list
    for (int i = 0; i < playerCount; i++)
    {
        addPlayer(&head, players[i]);
    }

    printf("Loaded %d players successfully!\n", playerCount);

    int choice;
    
    while (1)
    {
        printf("\n------- MENU ------- \n");
        printf("1. Display all players of a Team\n");
        printf("2. Display Teams by Average Batting Strike Rate\n");
        printf("3. Display Top K Players of a Team by Role\n");
        printf("4. Display Overall Top K Players (All Teams)\n");
        printf("5. Exit\n");
        printf("------------------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        if (choice == 1)
        {
            char teamInput[50];
            validString("Enter Team Name: ", teamInput);

            displayPlayersOfTeam(head, teamInput);
        }
        else if (choice == 2)
        {
            displayTeamByStrikeRate(head);
        }
        else if (choice == 3)
        {
            char teamInput[50], roleInput[50];
            int K;

            validString("Enter Team Name: ", teamInput);
            validString("Enter Role (Batsman/Bowler/All-rounder): ", roleInput);

            

            printf("Enter K value: ");
            scanf("%d", &K);
            getchar();

            displayTopKPlayers(head, teamInput, roleInput, K);
        }
        else if (choice == 4)
        {
            int K;
            printf("Enter K value: ");
            scanf("%d", &K);
            getchar();

            displayOverallTopK(head, K);
        }
        else if (choice == 5)
        {
            printf("Exiting..\n");
            break;
        }
        else
        {
            printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}