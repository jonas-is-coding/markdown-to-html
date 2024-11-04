const vscode = require('vscode');
const { spawn } = require('child_process');
const path = require('path');

function activate(context) {
    console.log('Markdown to HTML Converter is now active!');
    
    // Status Bar Item erstellen
    let myStatusBarItem = vscode.window.createStatusBarItem(
        vscode.StatusBarAlignment.Right,
        100
    );
    
    // Command ID muss mit der in package.json übereinstimmen
    myStatusBarItem.command = 'markdown-to-html.convert';
    myStatusBarItem.text = "$(file-code) Convert to HTML";
    myStatusBarItem.tooltip = "Convert Markdown to HTML";
    
    // Status Bar Item zum Context hinzufügen
    context.subscriptions.push(myStatusBarItem);
    
    // Update Status Bar wenn sich der aktive Editor ändert
    function updateStatusBarItem() {
        const editor = vscode.window.activeTextEditor;
        if (editor && editor.document.languageId === 'markdown') {
            myStatusBarItem.show();
        } else {
            myStatusBarItem.hide();
        }
    }
    
    // Event Listener für Editor-Wechsel
    context.subscriptions.push(
        vscode.window.onDidChangeActiveTextEditor(() => {
            updateStatusBarItem();
        })
    );
    
    // Initial Update
    updateStatusBarItem();
    
    // Command Registration
    let disposable = vscode.commands.registerCommand('markdown-to-html.convert', async function () {
        const editor = vscode.window.activeTextEditor;
        if (!editor) {
            vscode.window.showErrorMessage('Kein aktiver Editor gefunden');
            return;
        }

        if (editor.document.languageId !== 'markdown') {
            vscode.window.showErrorMessage('Aktuelle Datei ist keine Markdown-Datei');
            return;
        }

        try {
            const converterPath = path.join(context.extensionPath, 'src/markdown-converter');

            console.log(`Converter Path: ${converterPath}`);
            
            await editor.document.save();
            
            const inputPath = editor.document.uri.fsPath;
            const outputPath = inputPath.replace('.md', '.html');

            const process = spawn(converterPath, [inputPath, outputPath]);

            process.stdout.on('data', (data) => {
                console.log(`stdout: ${data}`);
            });

            process.stderr.on('data', (data) => {
                console.error(`stderr: ${data}`);
                vscode.window.showErrorMessage(`Konvertierung fehlgeschlagen: ${data}`);
            });

            process.on('close', (code) => {
                if (code === 0) {
                    vscode.window.showInformationMessage('Markdown erfolgreich zu HTML konvertiert!');
                    vscode.workspace.openTextDocument(outputPath).then(doc => {
                        vscode.window.showTextDocument(doc);
                    });
                } else {
                    vscode.window.showErrorMessage(`Prozess mit Code ${code} beendet`);
                }
            });
        } catch (error) {
            vscode.window.showErrorMessage(`Fehler bei der Konvertierung: ${error.message}`);
        }
    });
    
    context.subscriptions.push(disposable);
}

function deactivate() {}

module.exports = {
    activate,
    deactivate
};