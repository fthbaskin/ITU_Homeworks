// Fatih Baskın
// 150210710

#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

int main()
{
    // Ask for number of resources and processes.
    printf("Please provide number of resources.\n");
    int num_resources;
    scanf("%d", &num_resources);
    printf("Please provide number of processes.\n");
    int num_processes;
    scanf("%d", &num_processes);

    // Read necessary information from files.
    FILE *fp = fopen("allocations.txt", "r");
    assert(fp > 0);
    int process_allocations[num_processes][num_resources];
    for (int i = 0; i < num_processes; i++)
        for (int j = 0; j < num_resources; j++)
            fscanf(fp, "%d", &process_allocations[i][j]);
    fclose(fp);
    fp = fopen("requests.txt", "r");
    assert(fp > 0);
    int process_requests[num_processes][num_resources];
    for (int i = 0; i < num_processes; i++)
        for (int j = 0; j < num_resources; j++)
            fscanf(fp, "%d", &process_requests[i][j]);
    fclose(fp);
    fp = fopen("resources.txt", "r");
    assert(fp > 0);
    int resources[num_resources];
    for (int i = 0; i < num_resources; i++)
        fscanf(fp, "%d", &resources[i]);
    fclose(fp);

    // Print preliminary information.
    printf("Total number of resources: ");
    for (int i = 0; i < num_resources - 1; i++)
        printf("R%d:%d ", i + 1, resources[i]);
    printf("R%d:%d\n", num_resources, resources[num_resources - 1]);
    for (int i = 0; i < num_processes; i++)
    {
        printf("Process %d information:\nAllocated resources: ", i + 1);
        for (int j = 0; j < num_resources - 1; j++)
            printf("R%d:%d ", j + 1, process_allocations[i][j]);
        printf("R%d:%d\nRequested resources: ", num_resources, process_allocations[i][num_resources - 1]);
        for (int j = 0; j < num_resources - 1; j++)
            printf("R%d:%d ", j + 1, process_requests[i][j]);
        printf("R%d:%d\n", num_resources, process_requests[i][num_resources - 1]);
    }

    // After printing necessary info, calculate total remaining resources.
    // By moving trough processes and deducing from the total resources.
    int remaining_resources[num_resources];
    for (int i = 0; i < num_resources; i++)
    {
        remaining_resources[i] = resources[i];
        for (int j = 0; j < num_processes; j++)
            remaining_resources[i] -= process_allocations[j][i];
    }

    /* This was for debugging
    for (int i = 0; i < num_processes; i++)
        printf("%d", remaining_resources[i]);
     */

    // After calculating remaining resources, calculate work queue.
    int work_queue[num_processes];
    for (int i = 0; i < num_processes; i++)
        work_queue[i] = 0;
    bool process_info[num_processes];
    for (int i = 0; i < num_processes; i++)
        process_info[i] = false;
    int work_idx = 0;

    // This flag (out of the while loop) is required for detecting whether there is a deadlock.
    bool is_deadlock = false;

    // Calculation of the work queue done iteratively.
    while (work_idx < num_processes)
    {
        // A flag is required, if there isn't any possible process to run, then remaining processes are causing a deadlock. By default it is true.
        bool deadlock_flag = true;

        // Then, iteritavely pool trough processes and if a process is okey to run, modify flag, update process_info and add that process into process queue.
        for (int i = 0; i < num_processes; i++)
        {
            // If currently being checked process is ran before, skip it.
            if (process_info[i])
                continue;

            // This flag holds necessary information to whether run this process
            bool run_flag = true;

            // If there is not enough resources for the current process, skip current process (set flag to false) otherwise run this process
            for (int j = 0; j < num_resources; j++)
            {
                if (process_requests[i][j] > remaining_resources[j])
                {
                    run_flag = false;
                    break;
                }
            }

            // If the current process can be run, then modify deadlock flag, process info, remaining resources, process queue and break the current process loop.
            if (run_flag)
            {
                // Modify the deadlock flag.
                deadlock_flag = false;

                // Name of the process is index + 1 (naming starts from 1, index starts from 0) and adding process name into work queue.
                work_queue[work_idx] = i + 1;
                work_idx += 1;

                // Modifying the process info.
                process_info[i] = true;

                // Modifying the resources since this process will run and when it finishes, it will free its resources.
                for (int j = 0; j < num_resources; j++)
                    remaining_resources[j] += process_allocations[i][j];

                // Finally, breaking the process for loop to start all over again.
                break;
            }
        }

        // If deadlock flag didn't get modified by an appropiate process, then there is a deadlock. Set deadlock status to true and break out of while loop.
        if (deadlock_flag)
        {
            is_deadlock = true;
            break;
        }
    }

    // Now, the running order of processes and deadlocking processes are printed.
    printf("Running order of processes:");
    for (int i = 0; i < num_processes; i++)
    {
        if (work_queue[i] != 0)
            printf(" P%d", work_queue[i]);
        else
        {
            printf("\n");
            break;
        }
    }

    // Print deadlock information.
    if (is_deadlock)
    {
        printf("There is a deadlock. ");
        // Print the processes that are not set as true (ran) in the while loop above since they are causing a deadlock.
        for (int i = 0; i < num_processes; i++)
        {
            if (process_info[i] == false)
                printf("P%d ", i + 1);
        }
        printf("is/are causing a deadlock.\n");
    }
    else
    {
        printf("No deadlock occurs.\n");
    }

    return 0;
}