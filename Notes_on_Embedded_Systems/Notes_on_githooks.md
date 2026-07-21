# Notes on githooks

References: 
 - https://learn.microsoft.com/en-us/training/modules/explore-git-hooks/
 - https://git-scm.com/docs/githooks
 - https://learn.microsoft.com/en-us/azure/devops/service-hooks/events
 - https://learn.microsoft.com/en-us/azure/devops/repos/git/branch-policies
 - https://github.com/andrewseidl/githook-clang-format
 - https://github.com/pocc/pre-commit-hooks
 - https://gist.github.com/JulianKnodt/fee4da06b9ca860e65e7132bf91590fa
 - https://github.com/barisione/clang-format-hooks/tree/master
 - https://github.com/codeocelot/git-diff-lint/blob/master/git-diff-lint

## Introduction to Git hooks

Git hooks can change how teams approach code quality, security, and following company rules. Instead of checking these things later in the process, 
Git hooks let teams add automatic checks directly into the development workflow. This creates quality standards that work automatically across teams and projects.

### Why automation matters

Modern software development needs automation that works precisely at every stage. Git hooks provide the foundation for this automation. 
They let teams implement quality checks, security validations, and rule compliance that run automatically without slowing down developers.

 - Check problems early: Git hooks help teams use "shift-left" strategies that catch problems at the earliest possible point. This reduces the cost of fixing issues and improves overall software quality.
 - Security first model: In business environments, Git hooks work as automatic security guards. They check every code change against security policies before allowing it to continue through the development process.
 - Automatic rule checking: For companies that must follow strict regulations, Git hooks provide automatic compliance checking. This ensures every code change meets necessary standards without requiring manual review.

### Hooks on developer computers

Client-side hooks run on each developer's computer. They provide immediate feedback and prevent bad code from entering shared code repositories.

### Pre-commit hook features

 - Code quality checks: Automatically check code formatting, linting rules, and company coding standards before allowing commits.
 - Security scanning: Run automatic security scans to find passwords, API keys, and vulnerable dependencies before they enter the code.
 - Test running: Run specific test suites to make sure code changes don't break existing functionality.
 - Documentation checks: Verify that code changes include proper documentation updates and maintain documentation standards.

### Commit message hook automation

 - prepare-commit-msg: Automatically create or modify commit messages to ensure consistency with company standards and include necessary information.
 - commit-msg: Check commit message format, enforce naming rules, and ensure proper links to work items or issue tracking systems.

### Post-commit integration features

 - Notification automation: Send automatic notifications to team members, project management systems, or collaboration platforms.
 - Documentation creation: Automatically update project documentation, API references, or change logs based on commit content.
 - Metrics collection: Gather development metrics and analytics to support continuous improvement efforts.

## Advanced hook implementation patterns

## Security-focused hook strategies

Password and secret detection:

```bash
#!/bin/bash
# Check for passwords and secrets in code changes
if git diff --cached --name-only | xargs grep -l -E "(password|secret|api[_-]?key|token|credential)" 2>/dev/null; then
    echo "Security Alert: Found potential passwords or secrets in your changes"
    echo "Please review and remove sensitive information before committing"
    exit 1
fi
```

Checking for vulnerable dependencies:

```bash
#!/bin/bash
# Check for security vulnerabilities in dependencies
if command -v npm &> /dev/null && [ -f package.json ]; then
    npm audit --audit-level=high
    if [ $? -ne 0 ]; then
        echo "Found security vulnerabilities in dependencies"
        echo "Please fix high-severity vulnerabilities before committing"
        exit 1
    fi
fi
```

## Quality checking hook automation

Complete code quality checking:

```bash
#!/bin/bash
# Check code quality for multiple programming languages
for file in $(git diff --cached --name-only --diff-filter=ACM); do
    case "$file" in
        *.js|*.ts)
            npx eslint "$file" || exit 1
            ;;
        *.py)
            python -m flake8 "$file" || exit 1
            python -m mypy "$file" || exit 1
            ;;
        *.cs)
            dotnet format --verify-no-changes --include "$file" || exit 1
            ;;
    esac
done
```

Automatic test running strategy:

```bash
#!/bin/bash
# Smart test running based on what changed
changed_files=$(git diff --cached --name-only)
if echo "$changed_files" | grep -q "src/"; then
    echo "Running unit tests for changed components..."
    npm test -- --findRelatedTests $changed_files
    if [ $? -ne 0 ]; then
        echo "Tests failed. Please fix failing tests before committing"
        exit 1
    fi
fi
```

## Integration with development tools

## Azure DevOps integration
Work item link checking:

```bash
#!/bin/bash
# Make sure commit messages include Azure DevOps work item references
commit_message=$(cat "$1")
if ! echo "$commit_message" | grep -qE "#[0-9]+|AB#[0-9]+"; then
    echo "Commit message must reference a work item (e.g., #1234 or AB#1234)"
    exit 1
fi
```
Branch name checking:
```bash
#!/bin/bash
# Check branch naming rules align with Azure DevOps policies
current_branch=$(git branch --show-current)
if ! echo "$current_branch" | grep -qE "^(feature|bugfix|hotfix)/[a-z0-9-]+$"; then
    echo "Branch name must follow convention: feature/description, bugfix/description, or hotfix/description"
    exit 1
fi
```

### Pipeline integration automation

**Note**: You need to install the Azure DevOps CLI extension to use these commands.

Build validation triggers:
```bash
#!/bin/bash
# Trigger Azure Pipelines validation builds for significant changes
if git diff --cached --name-only | grep -qE "\.(cs|js|ts|py)$"; then
    echo "Triggering validation build for code changes..."
    az pipelines build queue --definition-name "PR-Validation" --branch $(git branch --show-current)
fi
```

## Hook categories and use cases

### Quality gate automation

Pre-commit quality gates:
 - Code formatting and style checking
 - Static analysis and linting
 - Unit test running for changed code
 - Documentation completeness checking
 - Performance impact checking
 - Pre-push validation:

Integration test running:
 - Security vulnerability scanning
 - Dependency license compliance checking
 - Build validation and artifact creation
 - Deployment readiness checking
 - Security and complia

### Security and compliance automation

Security hook implementation:
 - Password and secret detection
 - Dependency vulnerability checking
 - Code security pattern validation
 - Compliance rule checking
 - Audit trail creation
  
Compliance validation hooks:
 - Regulatory requirement checking
 - Code signing and verification
 - Change approval validation
 - Documentation requirement checking
 - Audit log creation

### Development workflow enhancement

Developer experience optimization:
 - Automatic commit message creation
 - Branch naming rule checking
 - Work item linking automation
 - Code review assignment automation
 - Progress tracking and reporting

Team collaboration enhancement:
 - Notification and communication automation
 - Knowledge sharing help
 - Metrics collection and reporting
 - Process compliance monitoring
 - Continuous improvement data gathering

Git hooks provide the essential automation foundation for development teams.
They help organizations add quality, security, and compliance directly into the
development workflow while keeping developers productive and happy.


## Implement Git hooks

Git hooks implementation requires careful thinking about cross-platform compatibility,
maintainability, and team deployment strategies. Modern approaches focus on version-controlled
hook management and automatic distribution rather than manual setup.


### Cross-platform hook development
Modern development environments need Git hooks that work the same way across Windows, macOS, and Linux development environments.

### Universal implementation


```bash
#!/usr/bin/env bash
# Cross-platform compatible shebang that automatically finds bash interpreter
# Works consistently across Windows Git Bash, macOS, and Linux environments
```
This approach removes the platform-specific path problems that cause issues with traditional 
implementations and ensures consistent behavior across different development environments.

### Environment detection strategy
```bash
#!/usr/bin/env bash
# Smart environment detection for platform-specific optimizations
detect_environment() {
    if [[ "$OSTYPE" == "msys" ]] || [[ "$OSTYPE" == "win32" ]]; then
        PLATFORM="windows"
        PYTHON_CMD="python"
    elif [[ "$OSTYPE" == "darwin"* ]]; then
        PLATFORM="macos"
        PYTHON_CMD="python3"
    else
        PLATFORM="linux"
        PYTHON_CMD="python3"
    fi
}
```

### Security-focused credential detection

Implement sophisticated credential detection that goes beyond simple keyword matching:

```bash
#!/usr/bin/env bash
# Advanced credential detection with pattern recognition

check_credentials() {
    local staged_files=$(git diff --cached --name-only)
    local violations=""

    # Define comprehensive credential patterns
    local patterns=(
        "password\s*[=:]\s*['\"][^'\"]{8,}"
        "api[_-]?key\s*[=:]\s*['\"][^'\"]{20,}"
        "secret\s*[=:]\s*['\"][^'\"]{16,}"
        "token\s*[=:]\s*['\"][^'\"]{24,}"
        "-----BEGIN\s+(RSA\s+)?PRIVATE\s+KEY-----"
        "mysql://.*:.*@"
        "postgresql://.*:.*@"
    )

    for file in $staged_files; do
        if [ -f "$file" ]; then
            for pattern in "${patterns[@]}"; do
                if git show ":$file" | grep -qiE "$pattern"; then
                    violations+="Potential credential detected in $file\n"
                fi
            done
        fi
    done

    if [ ! -z "$violations" ]; then
        echo -e "Security Alert: Credential Detection\n"
        echo -e "$violations"
        echo -e "Please remove sensitive information before committing\n"
        return 1
    fi

    return 0
}

# Execute security validation
check_credentials || exit 1
```

### Comprehensive code quality validation

Implement multi-language code quality enforcement that adapts to your technology stack:

```bash
#!/usr/bin/env bash
# Enterprise code quality validation framework

validate_code_quality() {
    local staged_files=$(git diff --cached --name-only --diff-filter=ACM)
    local quality_violations=0

    echo "Performing code quality validation..."

    for file in $staged_files; do
        case "$file" in
            *.js|*.jsx|*.ts|*.tsx)
                if command -v npx >/dev/null 2>&1; then
                    echo "Linting JavaScript/TypeScript: $file"
                    npx eslint "$file" || ((quality_violations++))

                    if [[ "$file" =~ \.(ts|tsx)$ ]]; then
                        echo "Type checking: $file"
                        npx tsc --noEmit --skipLibCheck "$file" || ((quality_violations++))
                    fi
                fi
                ;;
            *.py)
                if command -v python3 >/dev/null 2>&1; then
                    echo "Linting Python: $file"
                    python3 -m flake8 "$file" || ((quality_violations++))

                    if command -v mypy >/dev/null 2>&1; then
                        echo "Type checking Python: $file"
                        python3 -m mypy "$file" || ((quality_violations++))
                    fi
                fi
                ;;
            *.cs)
                if command -v dotnet >/dev/null 2>&1; then
                    echo "Formatting C#: $file"
                    dotnet format --verify-no-changes --include "$file" || ((quality_violations++))
                fi
                ;;
            *.go)
                if command -v go >/dev/null 2>&1; then
                    echo "Formatting Go: $file"
                    if ! gofmt -l "$file" | grep -q .; then
                        gofmt -w "$file"
                        git add "$file"
                    fi

                    echo "Linting Go: $file"
                    golint "$file" || ((quality_violations++))
                fi
                ;;
        esac
    done

    if [ $quality_violations -gt 0 ]; then
        echo "Code quality validation failed with $quality_violations violations"
        echo "Please fix the issues above before committing"
        return 1
    fi

    echo "Code quality validation passed"
    return 0
}

# Execute quality validation
validate_code_quality || exit 1
```

### Intelligent test execution strategy

Implement smart test execution that runs only relevant tests based on changed code:

```bash
#!/usr/bin/env bash
# Intelligent test execution based on change impact

execute_relevant_tests() {
    local changed_files=$(git diff --cached --name-only)
    local test_failures=0

    echo "Analyzing test requirements for changed files..."

    # Check if source code changes require testing
    if echo "$changed_files" | grep -qE "\.(js|jsx|ts|tsx|py|cs|go)$"; then
        echo "Source code changes detected, running relevant tests..."

        # JavaScript/TypeScript projects
        if [ -f "package.json" ] && command -v npm >/dev/null 2>&1; then
            if echo "$changed_files" | grep -qE "\.(js|jsx|ts|tsx)$"; then
                echo "Running JavaScript/TypeScript tests..."
                npm test -- --findRelatedTests $changed_files --passWithNoTests || ((test_failures++))
            fi
        fi

        # Python projects
        if [ -f "requirements.txt" ] || [ -f "pyproject.toml" ]; then
            if echo "$changed_files" | grep -qE "\.py$"; then
                echo "Running Python tests..."
                if command -v pytest >/dev/null 2>&1; then
                    pytest --tb=short || ((test_failures++))
                elif command -v python3 >/dev/null 2>&1; then
                    python3 -m unittest discover || ((test_failures++))
                fi
            fi
        fi

        # .NET projects
        if find . -name "*.csproj" -o -name "*.sln" | grep -q .; then
            if echo "$changed_files" | grep -qE "\.cs$"; then
                echo "Running .NET tests..."
                dotnet test --no-build --verbosity minimal || ((test_failures++))
            fi
        fi

        # Go projects
        if [ -f "go.mod" ]; then
            if echo "$changed_files" | grep -qE "\.go$"; then
                echo "Running Go tests..."
                go test ./... || ((test_failures++))
            fi
        fi
    fi

    if [ $test_failures -gt 0 ]; then
        echo "Test execution failed"
        echo "Please fix failing tests before committing"
        return 1
    fi

    echo "All relevant tests passed"
    return 0
}

# Execute intelligent testing
execute_relevant_tests || exit 1
```

### Prepare-commit-msg hook implementation

Automate commit message generation to ensure consistency and include necessary metadata:

```bash
#!/usr/bin/env bash
# Automated commit message enhancement with Azure DevOps integration

enhance_commit_message() {
    local commit_msg_file="$1"
    local commit_source="$2"
    local sha="$3"

    # Skip automation for merge commits, amend commits, etc.
    if [ -n "$commit_source" ]; then
        return 0
    fi

    # Get current branch information
    local current_branch=$(git branch --show-current)
    local branch_prefix=""

    # Extract work item ID from branch name if present
    if [[ "$current_branch" =~ ^(feature|bugfix|hotfix)/([0-9]+) ]]; then
        local work_item_id="${BASH_REMATCH[2]}"
        branch_prefix="AB#$work_item_id: "
    elif [[ "$current_branch" =~ ^(feature|bugfix|hotfix)/(.+)$ ]]; then
        local feature_name="${BASH_REMATCH[2]}"
        branch_prefix="[$feature_name] "
    fi

    # Read existing commit message
    local existing_message=$(cat "$commit_msg_file")

    # Only add prefix if not already present
    if [ ! -z "$branch_prefix" ] && ! echo "$existing_message" | grep -q "^$branch_prefix"; then
        # Create enhanced commit message
        echo "${branch_prefix}${existing_message}" > "$commit_msg_file"
    fi

    # Add commit template if message is empty
    if [ -z "$existing_message" ] || [ "$existing_message" = "" ]; then
        cat >> "$commit_msg_file" << EOF
${branch_prefix}Brief description of changes

# Detailed explanation of what and why changes were made
#
# Include:
# - What problem this solves
# - Why this approach was chosen
# - Any breaking changes or migration notes
#
# Link to work items: AB#1234
EOF
    fi
}

enhance_commit_message "$@"
```

### Commit message validation hook

Ensure commit messages meet organizational standards:

```bash
#!/usr/bin/env bash
# Comprehensive commit message validation

validate_commit_message() {
    local commit_msg_file="$1"
    local commit_message=$(cat "$commit_msg_file")

    # Remove comment lines for validation
    local clean_message=$(echo "$commit_message" | grep -v '^#' | sed '/^$/d')

    # Check minimum length
    if [ ${#clean_message} -lt 10 ]; then
        echo "Commit message too short (minimum 10 characters)"
        return 1
    fi

    # Check maximum length for first line
    local first_line=$(echo "$clean_message" | head -n1)
    if [ ${#first_line} -gt 72 ]; then
        echo "Commit message first line too long (maximum 72 characters)"
        echo "Current length: ${#first_line}"
        return 1
    fi

    # Check for work item reference in enterprise environments
    if ! echo "$clean_message" | grep -qE "(AB#[0-9]+|#[0-9]+|closes #[0-9]+|fixes #[0-9]+)"; then
        echo "Commit message should reference a work item (e.g., AB#1234 or #1234)"
        echo "Continue anyway? (y/N)"
        read -r response
        if [[ ! "$response" =~ ^[Yy]$ ]]; then
            return 1
        fi
    fi

    # Check for conventional commit format (optional)
    if echo "$first_line" | grep -qE "^(feat|fix|docs|style|refactor|test|chore)(\(.+\))?: "; then
        echo "Conventional commit format detected"
    fi

    echo "Commit message validation passed"
    return 0
}

validate_commit_message "$@" || exit 1
```

## Azure DevOps integration

### Server-side hook integration

Use Azure DevOps service hooks for server-side automation:

```bash
#!/usr/bin/env bash
# Azure DevOps webhook integration for advanced workflows

trigger_azure_validation() {
    local branch_name=$(git branch --show-current)
    local commit_sha=$(git rev-parse HEAD)

    # Trigger Azure Pipelines validation build
    if command -v az >/dev/null 2>&1; then
        echo "Triggering Azure DevOps validation pipeline..."

        az pipelines build queue \
            --definition-name "PR-Validation" \
            --branch "$branch_name" \
            --commit-id "$commit_sha" \
            --output table
    fi
}

# Integration with Azure Boards
update_work_item() {
    local commit_message="$1"

    # Extract work item ID from commit message
    if [[ "$commit_message" =~ AB#([0-9]+) ]]; then
        local work_item_id="${BASH_REMATCH[1]}"

        echo "Updating Azure Boards work item #$work_item_id..."

        # Add commit information to work item
        az boards work-item update \
            --id "$work_item_id" \
            --discussion "Commit $(git rev-parse --short HEAD): $(echo "$commit_message" | head -n1)"
    fi
}
```

## Performance optimization and best practices

### Hook performance guidelines

Implement performance optimizations to maintain developer productivity:

```bash
#!/usr/bin/env bash
# Performance-optimized hook implementation

optimize_hook_performance() {
    # Cache expensive operations
    local cache_dir=".git/hooks-cache"
    mkdir -p "$cache_dir"

    # Only run expensive checks on changed files
    local changed_files=$(git diff --cached --name-only)

    # Implement timeout protection
    timeout 30s expensive_operation || {
        echo "Hook operation timed out, skipping..."
        return 0
    }

    # Provide progress feedback for long operations
    echo "Running validation (this may take a moment)..."
}

# Implement graceful degradation
fallback_validation() {
    echo "Primary validation failed, running minimal checks..."
    # Implement basic validation as fallback
}
```
