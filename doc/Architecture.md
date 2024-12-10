# Architecture

## Threading Model

* Render Process [Mother]
    * Read user input
    * Swap frame buffer
    * Start Physics Step
    * Render next frame
    * Wait for Physics Step
* Physics Process
* Loader Process