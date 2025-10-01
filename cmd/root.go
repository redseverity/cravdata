/*
Copyright © 2025 redseverity <red.severity723@passfwd.com>
*/
package cmd

import (
	"os"

	"github.com/spf13/cobra"
)

// rootCmd represents the base command when called without any subcommands
var rootCmd = &cobra.Command{
	Use: "cravdata",
	// Short: "",
	// Long: ``,
	// Run: func(cmd *cobra.Command, args []string) { },
}

// This is called by main.main().
func Execute() {
	err := rootCmd.Execute()
	if err != nil {
		os.Exit(1)
	}
}

func init() {}
