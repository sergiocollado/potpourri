# Notes on github actions

## What are github actions

GitHub Actions is a platform for automating developer workflows directly within GitHub repositories. It enables you to build, test, and deploy your code automatically when specific events occur in your repository.

**Actions** are individual tasks that you can combine to create custom workflows. Think of them as reusable units of code that perform specific functions.

**Workflows** are automated processes made up of one or more actions. They run when triggered by events in your repository.


## Common user cases

GitHub Actions excels at automating various development tasks:

### CI/CD pipelines
 - Continuous Integration: Automatically build and test code on every push or pull request.
 - Continuous Deployment: Deploy applications to staging or production environments.
 - Multi-environment deployments: Deploy to different environments based on branch rules.

### Code quality and security
 - Automated testing: Run unit tests, integration tests, and end-to-end tests.
 - Code analysis: Perform static code analysis and security scanning.
 - Dependency management: Automatically update dependencies and check for vulnerabilities.

### Project management automation
 - Issue triage: Automatically label and assign new issues.
 - Pull request management: Auto-merge dependabot updates or require reviews.
 - Release automation: Create releases and generate changelogs automatically.

## How actions work

Actions are defined using YAML files stored in the `.github/workflows` directory of your repository. These workflows:

 - Trigger on specific events (push, pull request, schedule, etc.).
 - Run on virtual machines called "runners" (GitHub-hosted or self-hosted).
 - Execute a series of steps that can include pre-built actions or custom scripts.

You can also create custom actions using Docker containers, JavaScript, or composite actions that combine multiple steps.

## The GitHub Actions execution flow

## Event detection and triggering

GitHub continuously monitors your repository for specific events that can initiate workflows:

### Repository events:

### Code pushes to branches
 - Pull request creation, updates, or merging
 - Issue creation or modification
 - Release publishing
 - Scheduled events:

### Cron-based time schedules
 - Recurring maintenance tasks
 - External events:

### Manual workflow triggers via GitHub UI or API
 - Webhook calls from external systems
 - Repository dispatch events from third-party integrations

## Workflow orchestration
Once triggered, GitHub Actions processes your workflow:

### Workflow parsing:
 - Reads the YAML workflow file from .github/workflows/
 - Validates syntax and configuration
 - Determines job dependencies and execution order

### Runner allocation:
 - Assigns appropriate runners (GitHub-hosted or self-hosted)
 - Provisions clean virtual environments for each job
 - Sets up required operating systems and software

## Job execution and coordination

Paralel executioin (default): 

```yaml
jobs:
  lint: # Runs simultaneously
  test: # Runs simultaneously
  security-scan: # Runs simultaneously
```

Sequential execution (with depencies)
```yaml
jobs:
  build:
    runs-on: ubuntu-latest

  test:
    needs: build # Waits for build to complete
    runs-on: ubuntu-latest

  deploy:
    needs: [build, test] # Waits for both jobs
    runs-on: ubuntu-latest
```

### Action execution within jobs

Each job executes its steps sequentially:
 - Environment preparation: Runner setup and checkout
 - Action resolution: Download and cache required actions
 - Step execution: Run commands and actions in order
 - Artifact handling: Save and share files between jobs
 - Cleanup: Tear down environment and release resources

### Results and feedback
Upon completion, GitHub Actions provides comprehensive feedback

Status reporting:
 - Individual step success/failure indicators
 - Job-level status and duration metrics
 - Overall workflow status and summary

Notification integration:
 - Email notifications for workflow failures
 - Slack, Teams, or custom webhook integration
 - Status checks on pull requests






```yaml

```
