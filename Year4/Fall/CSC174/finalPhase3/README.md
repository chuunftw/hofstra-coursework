# Phase 3: Three-Person Work Breakdown

## Goal

Compare a small MLP, a small tabular transformer, and a random forest on two tasks:

1. Catch-rate regression.
2. Generation 8 Smogon-tier classification (OU, UU, RU, NU, PU, ZU).

Each person owns one model family for **both tasks**, including implementation, hyperparameter tuning, evaluation, figures, and writing. Assign actual names to Person 1, Person 2, and Person 3 as a group.

## Separate Responsibilities

| Responsibility | Person 1: Data + Random Forest | Person 2: MLP | Person 3: Tabular Transformer |
| --- | --- | --- | --- |
| Shared setup contribution | Lead historical tier-label merge, name/form reconciliation, dataset audit, and shared preprocessing/split implementation | Independently check label matches, exclusions, and class counts | Check shared input format, group assignments, and actual split/fold compatibility |
| Model implementation | Random forest regressor and classifier | Small MLP regressor and classifier | Small tabular transformer regressor and classifier |
| Hyperparameter tuning | Maximum depth: 3, 5, unrestricted; minimum samples per leaf: 2, 5, 10 | Hidden layers: [16], [32], [64]; learning rates: 0.001, 0.0003 | Embedding sizes: 16, 32; attention blocks: 1, 2 |
| Results and figures | Own scores, tuning plots, sample-size learning curves, classification confusion matrix, and regression error analysis | Own scores, training/validation loss curves, tuning plots, sample-size learning curves, classification confusion matrix, and regression error analysis | Own scores, training/validation loss curves, tuning plots, sample-size learning curves, classification confusion matrix, and regression error analysis |
| Report writing | Dataset, shared preprocessing/splits, and random forest methods/results | MLP methods, training analysis, and results | Transformer methods, training analysis, and results |
| Final coordination | Combine the model owners' score tables; document dataset sources, counts, and exclusions | Coordinate report and slide assembly using everyone's completed content | Connect working model modules through main.py; coordinate README.txt and code.zip |
| Individual submission | Own work_distribution.pdf | Own work_distribution.pdf | Own work_distribution.pdf |

The tuning values above are starting search ranges, not already optimized settings. Record any justified changes.

**Responsibility boundary:** Each model owner supplies working code, figure generation, results, and finished writing, and fixes failures in their own module. Person 3 integrates modules rather than rewriting everyone's code. Person 2 organizes supplied report/slide content rather than writing the whole submission.

## Work Done Together

| Stage | Shared work | Completion condition |
| --- | --- | --- |
| 1. Validate data | Confirm historical tier source/date, audit name/form matches, resolve ZU labels, review exclusions and class counts | One verified eligible dataset per task, with documented label provenance |
| 2. Freeze experiment protocol | Agree on input features, group IDs, saved test/CV split indices, seed policy, preprocessing, metrics, tuning budget, module interface, and output names | Every model can consume the same task-specific data and splits |
| 3. Review initial runs | Check that all six model-task combinations run; inspect preprocessing and validation behavior | No leakage or incompatible assumptions across implementations |
| 4. Compare results | Review CV performance, overfitting, errors, class imbalance, and training cost | Shared explanation of model differences and limitations |
| 5. Final evaluation | Freeze model choices, run each owner's selected model on the untouched test set, and consolidate results | Complete training/validation/testing score tables for both tasks |
| 6. Write shared conclusions | Draft introduction, abstract, comparison/discussion, conclusion, future work, and check references | Consistent report supported by actual experiments |
| 7. Verify and rehearse | Run packaged code in a clean environment, check all figures and deliverables, rehearse and divide speaking time | Reproducible package, report within 10 pages, presentation within 5-10 minutes |

## Current Dataset Status

- Inspected raw file: All_Pokemon.csv, containing 1,032 rows and 44 columns.
- Excluding 50 Mega Evolution rows leaves 982 regression rows, all with catch-rate targets.
- The raw CSV does not include Smogon labels.
- The Phase 1 claim of 304 classification rows remains **provisional**, not verified.
- An initial direct-name matching pass against the October 29, 2022 Pokemon Showdown source found 171 explicit OU/UU/RU/NU/PU matches. This is not the completed classification dataset.
- ZU membership and remaining name/form matches need verification. Do not automatically convert every `(PU)` label to ZU.
- Historical source: https://github.com/smogon/pokemon-showdown/blob/aa8ec5a79c3bd99c104b165c2c65b64c78e7de12/data/formats-data.ts
- Use verified counts in the final report; explain any differences from earlier submissions.

## Shared Evaluation Rules

- Reserve approximately 20% of each task's eligible data for final testing; keep alternate forms of the same species together.
- Use three-fold cross-validation on the remaining approximately 80%, preserving class proportions where feasible. Check actual fold class/group coverage before finalizing splits.
- Every model uses the same saved splits within a task. Regression and classification may use different eligible rows and splits.
- Fit imputers, categorical encoders, and numerical scalers only on the training portion of each fold. Neural models use standardized numerical features; random forests need not use scaling.
- Exclude identifiers and target columns from model inputs, and agree on redundant-feature exclusions before training.
- Regression: report MAE and RMSE; select hyperparameters by lowest average validation RMSE. MAE describes typical absolute error in catch-rate units; RMSE emphasizes larger errors.
- Classification: report macro-F1 and accuracy; select hyperparameters by highest average validation macro-F1. Include per-class confusion matrices.
- Neural models: MSE loss for regression, cross-entropy for classification, Adam, small networks, and L2 regularization. Freeze all remaining settings before comparisons.
- During CV, train neural models for up to 200 epochs with patience of about 15 epochs based on validation loss; restore best weights. Record best epochs for the selected configuration. Refit on the non-test 80% using the median of those best epoch counts, then evaluate the untouched test set.
- Clearly label CV validation scores separately from final-refit training scores. Save fold-level scores so the combined table is interpretable.
- Keep test results out of hyperparameter and epoch selection.
- Training loss curves show loss across epochs. Sample-size learning curves show performance as training data size changes; these are different analyses. Random forests do not need artificial epoch-loss curves.

## Each Model Owner's Handoff

Before final integration, each person supplies:

- A runnable module using the agreed shared interface and environment.
- Configurations and a record of all tested hyperparameters.
- Selected settings, seeds, split identifiers, and training times.
- Fold-level validation results and final training/test predictions and metrics.
- Code generating their report-ready plots and tables.
- Written methods, findings, limitations, and relevant references.

Agree on the module interface early and perform a small integration run before full tuning. Dataset preparation should not prevent others from starting model scaffolding, but final experiments must use the verified shared data.

## Final Deliverables

| Deliverable | Requirement | Coordinator |
| --- | --- | --- |
| report.pdf | Academic-style report, maximum 10 pages: title, abstract, introduction, dataset, methods, training/analysis, results, discussion, conclusion, references | Person 2; all write and review |
| presentation.pdf | Slides for a 5-10 minute presentation | Person 2; all contribute and present |
| code.zip | All project code, README.txt with running instructions, and main.py producing every figure/plot used in the report and slides, including shared comparisons | Person 3; all supply and verify their own modules |
| work_distribution.pdf | A few paragraphs explaining how the group distributed work; each partner submits their own document on Canvas | Each person individually |

## Order of Work

1. Jointly finish and check the dataset and shared protocol.
2. Develop and tune the three model families separately, with an early integration check.
3. Freeze model choices and perform final test evaluation.
4. Compare results and assemble report, slides, and reproducible code.
5. Review all deliverables and rehearse together.

## Coursework References

- A1/code/analysis.py: learning-rate comparisons and loss curves (especially Part 3).
- A2/code/analysis.py: architecture comparisons (Part 3), training/validation/test separation, training-only scaling, loss curves, and restoring the best epoch (Part 4).
- Use A1/A2 as structural and conceptual references. Their exact hyperparameters are not automatically optimal for this dataset, and Phase 3 permits library implementations rather than rebuilding neural networks from scratch.
