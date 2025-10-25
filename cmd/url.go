/*
Copyright © 2025 redseverity <red.severity723@passfwd.com>
*/
package cmd

import (
	"github.com/redseverity/cravdata/cmd/docs/urldocs"
	"github.com/redseverity/cravdata/cmd/validators/urlvalidator"
	"github.com/spf13/cobra"
)

var (
	targetURL string
	marker    string
	charset   string
)

// urlCmd represents the url subcommand
var urlCmd = &cobra.Command{
	Use:   urldocs.Use,
	Short: urldocs.Short,
	Long:  urldocs.Long,

	Args: func(cmd *cobra.Command, args []string) error {
		if err := cobra.MinimumNArgs(1)(cmd, args); err != nil {
			return err
		}

		targetURL = args[0]

		if err := urlvalidator.ValidateURL(targetURL); err != nil {
			return err
		}

		if err := urlvalidator.ValidateMarker(targetURL, marker); err != nil {
			return err
		}

		if err := urlvalidator.ValidateCharset(&charset); err != nil {
			return err
		}

		return nil
	},

	RunE: func(cmd *cobra.Command, args []string) error {
		return nil
	},
}

func init() {
	rootCmd.AddCommand(urlCmd)
	urlCmd.Flags().StringVarP(&marker, "marker", "m", "{BRUTE}", urldocs.Marker)
	urlCmd.Flags().StringVarP(&charset, "charset", "c", "abc", urldocs.Charset)
}
